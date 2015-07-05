
#pragma once
#include <ChainRunner.h>
#include "testingIncludes.h"

class ChainRunnerTest : public ChainTest {
    void SetUp() {
        ChainTest::SetUp();
    }
};

/**TEST_F(ChainRunner, DefaultConstructor)
{
   // auto chainRunner = new ChainRunner<int>();
   // delete(chainRunner);
    ASSERT_EQ(1, 1);
}*/
