
#pragma once
#include <ChainRunner.h>
#include "testingIncludes.h"

class ChainRunnerTest : public MCMCTest {
    std::unique_ptr<Chain<double>> chain;

    void SetUp() {
        MCMCTest::SetUp();
        chain.reset(new Chain<double>(proposalFunction, logPosterior, initialValue));
    }
};

/**TEST_F(ChainRunner, DefaultConstructor)
{
   // auto chainRunner = new ChainRunner<int>();
   // delete(chainRunner);
    ASSERT_EQ(1, 1);
}*/
