#pragma once
#include <globals.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include <Chain.h>
#include "testingIncludes.h"
#include "gmock/gmock.h"
#include "Chain.h"


#ifdef MKL
#include "mkl_vsl.h"
#endif

#define BRNG VSL_BRNG_MCG31
#define METHOD VSL_RNG_METHOD_GAUSSIAN_ICDF
#define SEED 1

using namespace ::testing;

class MCMCTest
{
    using paramType = double;
    using proposalFunctionTemplate = std::function<std::shared_ptr<paramType> (const std::shared_ptr<paramType> currentVal)>;
    using logPosteriorFunctionTemplate = std::function<double(const std::shared_ptr<paramType> Theta)>;

protected:
    double tolerance = 0.2;
    const unsigned long long nSamples = 4000000;
    double _initialValue = 12.3;
    std::shared_ptr<double> initialValue;
    double trueMean = 4;
    double trueVariance = 5;
    std::unique_ptr<gsl_rng> r;
    const gsl_rng_type* T = gsl_rng_default;
    VSLStreamStatePtr stream;

    proposalFunctionTemplate proposalFunction;
    logPosteriorFunctionTemplate logPosterior;

    // vector of normally distributed random variables.
    // initialized by populateNormalRv() which is called
    // in setup. It is size normalRvSize;
    const unsigned long long normalRvSize = 100000;
    std::unique_ptr<double> normalRv;
    int normalRvIndex = 0;
    // Populates the elements of normalRv
    // with draws from the standard normal distribution.

    std::shared_ptr<Chain<double>> chain;

    void setupNormalRv(int n)
    {
#ifdef MKL
        vdRngGaussian(METHOD, stream, n, normalRv.get(), 0, 1);
#else
        for (int i = 0; i < n; i++)
        {
            normalRv.get()[i] = gsl_ran_gaussian(r.get(), 1);
        }
#endif
    }
    // returns the next element of normalRvVec.
    // repopulates it if your at the last element.

    double getStdNormal()
    {
        if (normalRvIndex == normalRvSize - 1)
        {
            normalRvIndex = 0;
            setupNormalRv(normalRvSize);
        }
        normalRvIndex++;
        return normalRv.get()[(normalRvIndex) % normalRvSize];
    }

    virtual void SetUp()
    {
        gsl_rng_env_setup();
        r.reset(gsl_rng_alloc(T));

#ifdef MKL
        auto errcode = vslNewStream(&stream, BRNG, SEED);
#endif

        normalRv.reset((double*) calloc(normalRvSize, sizeof (double)));
        setupNormalRv(normalRvSize);

        proposalFunction = [this](std::shared_ptr<double> Theta) {
            double draw = *Theta + getStdNormal();
            std::shared_ptr<double> proposal(new double(draw));
            return proposal;
        };

        logPosterior = [&](std::shared_ptr<double> Theta) {
            double val = *Theta - trueMean;
            val = -0.5 * val * val / trueVariance;
            return val;
        };
        initialValue.reset(new double(_initialValue));
        chain.reset(
                new Chain<double>(proposalFunction, logPosterior, initialValue));
    }
};
