
#pragma once
#include <Chain.h>
#include "testingIncludes.h"

double tolerance = 0.005;
int n = 9000000000;


TEST(Chain, DefaultConstructor)
{
    auto chain = new Chain<int>();
    delete(chain);
    ASSERT_EQ(1, 1);
}

TEST(Chain, fullConstructor)
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



TEST(Chain, AcceptFunction)
{
    auto chain = new Chain<int>();
    auto llCurrent = std::log(0.5);
    auto llProposal = std::log(0.25);
    auto expectedProportion = 0.5;
    double proportionAccepted = 0;
    for (int i = 0; i < n; i++)
    {
        proportionAccepted += chain->accept(llCurrent, llProposal);
    }
    proportionAccepted /= n;
    ASSERT_LE(std::abs(proportionAccepted - expectedProportion), tolerance);
    delete(chain);
}


std::default_random_engine generator(std::random_device{}());
std::normal_distribution<double> distribution(0.0, 1.0);
double trueMean = 15.5;
double trueVariance = 4;
TEST(Chain, testConvergence)
{
    constexpr double testVal = 0.0;
    std::shared_ptr<double> initialValue(new double(testVal));
    std::shared_ptr<double> (*proposalFunction)(std::shared_ptr<double> Theta) =
        [](std::shared_ptr<double> Theta)
        {
            double draw = *Theta + distribution(generator);
            std::shared_ptr<double> proposal(new double(draw));
            return proposal;
        };
    double (*logPosterior)(std::shared_ptr<double> Theta) =
        [](std::shared_ptr<double> Theta)
    {   
        double val = *Theta - trueMean ;
        val = -0.5*val*val/trueVariance;
        return val;
    };

    auto chain =
        new Chain<double>(proposalFunction, logPosterior, initialValue);
    double mean = 0.0;
    double secondMoment = 0.0;
    for (int i = 0; i < n; i++)
    {
        auto currentVal = *(chain->currentTheta);
        mean += currentVal;
        secondMoment += std::pow(currentVal, 2);
        chain->step();
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

