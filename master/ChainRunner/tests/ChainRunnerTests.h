
#pragma once
#include <ChainRunner.h>
#include <DatabaseTest.h>
#include <MCMCTest.h>
class ChainRunnerTest : public MCMCTest, public DatabaseTest, public Test
{
    private:
        std::shared_ptr<ChainRunner<double>> m_chainRunner;
        
        public:
    void SetUp()
    {
        MCMCTest::SetUp();
        DatabaseTest::SetUp();
        m_chainRunner.reset(new ChainRunner<double>(mcmcConnection, chain));
    }
};

TEST_F(ChainRunnerTest, Constructor)
{

}
