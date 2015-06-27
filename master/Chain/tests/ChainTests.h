
#pragma once
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include <Chain.h>
#include "testingIncludes.h"
#include "gmock/gmock.h"

using namespace ::testing;

class ChainTest : public Test
{
    public:
	double tolerance = 0.0001;
	double trueMean = 15.5;
	double trueVariance = 4;
	const int n = 100000000;
        std::unique_ptr<gsl_rng> r;
        const gsl_rng_type* T = gsl_rng_default;

        virtual void SetUp()
        {
            gsl_rng_env_setup();
            r.reset(gsl_rng_alloc (T));
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

    #pragma omp parallel shared(proportionAccepted) 
    for (int i = 0; i < n; i++)
    {
        auto val = chain->accept(llCurrent, llProposal);
        #pragma omp critical
	proportionAccepted += val;
    }
    proportionAccepted /= n;
    ASSERT_LE(std::abs(proportionAccepted - expectedProportion), tolerance);
    delete(chain);
}


TEST_F(ChainTest, testConvergence)
{
    gsl_rng_env_setup();
    const gsl_rng_type* T = gsl_rng_default;
    gsl_rng * r = gsl_rng_alloc (T);

    constexpr double testVal = 0.0;
    std::shared_ptr<double> initialValue(new double(testVal));
    auto proposalFunction =
	[&T, &r](std::shared_ptr<double> Theta)
	{
            double draw = *Theta + gsl_ran_gaussian(r, 1);
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

    #pragma omp parallel shared(proportionAccepted) 
    for (int i = 0; i < n; i++)
    {
	auto currentVal = *(chain->currentTheta);
	chain->step();
        #pragma omp critical
	mean += currentVal;
	secondMoment += std::pow(currentVal, 2);
    }
    mean /= n;
    secondMoment /= n;
    double variance = secondMoment - std::pow(mean, 2);
    std::cout << "mean = " <<  mean << std::endl;
    std::cout << "variance = " <<  variance << std::endl;
    ASSERT_LE(mean - trueMean, tolerance);
    ASSERT_LE(variance - trueVariance, tolerance);
    delete(chain);
}
