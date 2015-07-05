
#pragma once
#include <MCMCTest.h>

class ChainTest : public MCMCTest
{
    public:
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
