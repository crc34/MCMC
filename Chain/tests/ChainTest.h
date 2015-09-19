
#pragma once
#include <globals.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include <Chain.h>
#include "gmock/gmock.h"
#include "Chain.h"
#include "GlobalDefines.h"
#include "gmock/gmock.h"
#include <math.h>
using namespace ::testing;

class ChainTest : public Test
{
public:
    const unsigned long long nSamples = 4000000;
    using paramType = double;
    using proposalFunctionTemplate =
            std::function<std::shared_ptr<paramType> (
            const std::shared_ptr<paramType> currentVal)>;
    using logPosteriorFunctionTemplate =
            std::function<double(const std::shared_ptr<paramType> Theta)>;
    double tolerance = 0.001;
    double _initialValue = 0;
    std::shared_ptr<double> initialValue;
    double trueMean = 4;
    double trueVariance = 2;
    std::unique_ptr<gsl_rng> r;
    const gsl_rng_type* T = gsl_rng_default;

    proposalFunctionTemplate proposalFunction;
    logPosteriorFunctionTemplate logPosterior;
    std::shared_ptr<Chain<double>> m_chain;

    virtual void SetUp()
    {
        gsl_rng_env_setup();
        r.reset(gsl_rng_alloc(T));

        proposalFunction = [this](std::shared_ptr<double> Theta) {
            double draw = *Theta + gsl_ran_gaussian_ziggurat(r.get(), 1);
            std::shared_ptr<double> proposal(new double(draw));
            return proposal;
        };

        logPosterior = [&](std::shared_ptr<double> Theta) {
            double val = *Theta - trueMean;
            val = -0.5 * val * val / trueVariance;
            return val;
        };
        initialValue.reset(new double(_initialValue));
        m_chain.reset(
                new Chain<double>(proposalFunction, logPosterior, initialValue));
    }
};

TEST_F(ChainTest, AcceptFunction)
{
    auto llCurrent = log(0.5);
    auto llProposal = log(0.25);
    auto expectedProportion = 0.5;
    double proportionAccepted = 0;

    for (int i = 0; i < nSamples; i++)
    {
        auto val = m_chain->accept(llCurrent, llProposal);
        proportionAccepted += val;
    }
    proportionAccepted /= nSamples;
    ASSERT_LE(abs(proportionAccepted - expectedProportion), tolerance);
}

TEST_F(ChainTest, testConvergence)
{
    double mean = 0.0;
    double secondMoment = 0.0;
    for (int i = 0; i < nSamples; i++)
    {
        auto currentVal = *(m_chain->m_currentTheta);
        m_chain->step();
        mean += currentVal;
        secondMoment += pow(currentVal, 2);
    }
    mean /= nSamples;
    secondMoment /= nSamples;
    double variance = secondMoment - pow(mean, 2);

    
    ASSERT_LE(mean - trueMean, tolerance);
    ASSERT_LE(variance - trueVariance, tolerance);
}
