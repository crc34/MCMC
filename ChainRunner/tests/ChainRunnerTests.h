#pragma once
#include <ChainRunner.h>
#include <DatabaseTest.h>
#include <MCMCTest.h>

class ChainRunnerTest : public MCMCTest, public DatabaseTest, public Test
{

public:
    std::shared_ptr<ChainRunner<double>> m_chainRunner;
    void SetUp()
    {
        MCMCTest::SetUp();
        DatabaseTest::SetUp();
        m_chainRunner.reset(new ChainRunner<double>(mcmcConnection, m_chain));
    }
};

TEST_F(ChainRunnerTest, RunChain)
{
    m_chainRunner->stepAndWrite();
}
