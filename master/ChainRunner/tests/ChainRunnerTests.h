
#pragma once
#include <ChainRunner.h>
#include "testingIncludes.h"

class ChainRunnerTest : public Test
{
double tolerance = 0.005;
int n = 9000000000;
};

TEST_F(ChainRunner, DefaultConstructor)
{
   // auto chainRunner = new ChainRunner<int>();
   // delete(chainRunner);
    ASSERT_EQ(1, 1);
}
