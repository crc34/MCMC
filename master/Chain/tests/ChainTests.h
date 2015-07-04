
#pragma once
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include <Chain.h>
#include "testingIncludes.h"
#include "gmock/gmock.h"

#define MKL

#ifdef MKL
#include "mkl_vsl.h"
#endif

using namespace ::testing;

#define BRNG VSL_BRNG_MCG31
#define METHOD VSL_RNG_METHOD_GAUSSIAN_ICDF
#define SEED 1

class ChainTest : public Test
{
    public:
	double tolerance = 0.009;
	double trueMean = 4;
	double trueVariance = 5;
	const int nSamples = 9000000;
        std::unique_ptr<gsl_rng> r;
        const gsl_rng_type* T = gsl_rng_default;
        VSLStreamStatePtr stream;

        // vector of normally distributed random variables.
        // initialized by populateNormalRv() which is called
        // in setup. It is size normalRvSize;
        int normalRvSize = 9000000;
        std::unique_ptr<double> normalRv;
        int normalRvIndex = 0;
        // Populates the elements of normalRv
        // with draws from the standard normal distribution.
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
            if(normalRvIndex == normalRvSize - 1)
            {
                normalRvIndex = 0;
                setupNormalRv(normalRvSize);
            }
            normalRvIndex++;
            return normalRv.get()[(normalRvIndex)%normalRvSize];
        }

        virtual void SetUp()
        {
            gsl_rng_env_setup();
            r.reset(gsl_rng_alloc (T));
            
            #ifdef MKL
            auto errcode = vslNewStream( &stream, BRNG, SEED );
            #endif

            normalRv.reset((double*)calloc(normalRvSize, sizeof(double)));
            setupNormalRv(normalRvSize);
        }
};

TEST_F(ChainTest, fullConstructor)
{
    constexpr double testVal = 12.3;
    std::shared_ptr<double> initialValue(new double(testVal));
    std::shared_ptr<double> (*proposalFunction)(std::shared_ptr<double> Theta) =
	[](std::shared_ptr<double> Theta){
	    std::shared_ptr<double> proposal(new double(testVal));
	    return proposal;
	};

    double (*logPosterior)(std::shared_ptr<double> Theta) =
	[](std::shared_ptr<double> Theta){
	return (*Theta)*(*Theta);
    };

    auto chain =
	new Chain<double>(proposalFunction, logPosterior, initialValue);
    ASSERT_EQ(*(chain->currentTheta), testVal);
    ASSERT_EQ(*(chain->proposalFunction(initialValue)), testVal);
    ASSERT_EQ(chain->logPosterior(initialValue), std::pow(testVal, 2));
    delete(chain);
}

TEST_F(ChainTest, AcceptFunction)
{
    auto chain = new Chain<int>();
    auto llCurrent = std::log(0.5);
    auto llProposal = std::log(0.25);
    auto expectedProportion = 0.5;
    double proportionAccepted = 0;

    for (int i = 0; i < nSamples; i++)
    {
        auto val = chain->accept(llCurrent, llProposal);
	proportionAccepted += val;
    }
    proportionAccepted /= nSamples;
    ASSERT_LE(std::abs(proportionAccepted - expectedProportion), tolerance);
    delete(chain);
}


TEST_F(ChainTest, testConvergence)
{

    constexpr double testVal = 0.0;
    std::shared_ptr<double> initialValue(new double(testVal));

    //TODO: create a vector of std normal rv's either using open mp
    // or the mkl rng so that these can be drawn faster
    auto proposalFunction =
	[this](std::shared_ptr<double> Theta)
	{
            double draw = *Theta + getStdNormal();
	    std::shared_ptr<double> proposal(new double(draw));
	    return proposal;
	};
    
    auto logPosterior =
	[&](std::shared_ptr<double> Theta)
    {   
	double val = *Theta - trueMean ;
	val = -0.5*val*val/trueVariance;
	return val;
    };

    auto chain =
	new Chain<double>(proposalFunction, logPosterior, initialValue);
    double mean = 0.0;
    double secondMoment = 0.0;

    for (int i = 0; i < nSamples; i++)
    {
	auto currentVal = *(chain->currentTheta);
	chain->step();
	mean += currentVal;
	secondMoment += std::pow(currentVal, 2);
    }
    mean /= nSamples;
    secondMoment /= nSamples;
    double variance = secondMoment - std::pow(mean, 2);
    std::cout << "mean = " <<  mean << std::endl;
    std::cout << "variance = " <<  variance << std::endl;
    ASSERT_LE(mean - trueMean, tolerance);
    ASSERT_LE(variance - trueVariance, tolerance);
    delete(chain);
}
