
#pragma once
#include <MCMCTest.h>
#include "testingIncludes.h"
#include "gmock/gmock.h"

class ChainTest : public MCMCTest, public Test
{
public:

    void SetUp()
    {
        MCMCTest::SetUp();
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
        if (i % 1000000 == 0)
        {
            std::cout << i << std::endl;
        }
    }
    mean /= nSamples;
    secondMoment /= nSamples;
    double variance = secondMoment - std::pow(mean, 2);
    std::cout << "mean = " << mean << std::endl;
    std::cout << "variance = " << variance << std::endl;
    ASSERT_LE(mean - trueMean, tolerance);
    ASSERT_LE(variance - trueVariance, tolerance);
}
