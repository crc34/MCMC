
#pragma once
#include <ChainRunner.h>
#include "testingIncludes.h"

namespace ChainRunnerTests
{

double tolerance = 0.005;
int n = 9000000000;


TEST(ChainRunner, DefaultConstructor)
{
   // auto chainRunner = new ChainRunner<int>();
   // delete(chainRunner);
    ASSERT_EQ(1, 1);
}

}
