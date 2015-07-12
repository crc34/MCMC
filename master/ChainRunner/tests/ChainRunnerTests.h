
#pragma once
#include <ChainRunner.h>
#include <DatabaseTest.h>
#include <MCMCTest.h>

class ChainRunnerTest : public MCMCTest, public DatabaseTest, public Test
{

private:

public:

    std::shared_ptr<ChainRunner<double>> m_chainRunner;

    void SetUp()
    {
        MCMCTest::SetUp();
        DatabaseTest::SetUp();
    }
};

TEST_F(ChainRunnerTest, Constructor)
{
    m_chainRunner.reset(new ChainRunner<double>(mcmcConnection, m_chain));
    ASSERT_EQ(1, 1);
}
