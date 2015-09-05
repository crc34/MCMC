#pragma once
#include <ChainRunner.h>
#include <DatabaseTest.h>
#include <MCMCTest.h>

class ChainRunnerTest : public MCMCTest, public DatabaseTest, public Test
{
public:
    std::unique_ptr<ChainRunner<double>> m_chainRunner;
    const int m_nSamples = 100000;
    const int m_flushingFrequency = 5000;
    void SetUp()
    {
        MCMCTest::SetUp();
        DatabaseTest::SetUp();
        m_chainRunner.reset(new ChainRunner<double>(mcmcConnection, m_chain));
    }
};

TEST_F(ChainRunnerTest, RunChain)
{
    for (int i = 0; i < m_nSamples; i++)
    {
        m_chainRunner->stepAndWrite(i, (i % m_flushingFrequency) != 0);
    }
 }
