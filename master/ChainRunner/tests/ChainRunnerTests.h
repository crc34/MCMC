
#pragma once
#include <ChainRunner.h>
#include "testingIncludes.h"

class ChainRunnerTest : public Test {
    double tolerance = 0.005;
    int nSamples = 9000;
    std::unique_ptr<MCMCDatabaseConnector> connection;
    std::unique_ptr<Chain<double>> chain;
    
    virtual void SetUp() {
        constexpr double testVal = 12.3;
        std::shared_ptr<double> initialValue(new double(testVal));
        std::shared_ptr<double> (*proposalFunction)(std::shared_ptr<double> Theta) =
                [](std::shared_ptr<double> Theta) {
                    std::shared_ptr<double> proposal(new double(testVal));
                    return proposal;
                };

        double (*logPosterior)(std::shared_ptr<double> Theta) =
                [](std::shared_ptr<double> Theta) {
                    return (*Theta)*(*Theta);
                };

        chain.reset(
            new Chain<double>(proposalFunction, logPosterior, initialValue));

    }
};

/**TEST_F(ChainRunner, DefaultConstructor)
{
   // auto chainRunner = new ChainRunner<int>();
   // delete(chainRunner);
    ASSERT_EQ(1, 1);
}*/
