
#pragma once
#include <MCMCTest.h>

class ChainTest : public MCMCTest
{
public:
    std::unique_ptr<Chain<double>> chain;

    void SetUp()
    {
        MCMCTest::SetUp();
        chain.reset(
                new Chain<double>(proposalFunction, logPosterior, initialValue));
    }

};

TEST_F(ChainTest, AcceptFunction)
{
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
}

TEST_F(ChainTest, testConvergence)
{
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
    std::cout << "mean = " << mean << std::endl;
    std::cout << "variance = " << variance << std::endl;
    ASSERT_LE(mean - trueMean, tolerance);
    ASSERT_LE(variance - trueVariance, tolerance);
}
