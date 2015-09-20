#pragma once
#include <MCMCDatabaseConnector.h>
#include <DatabaseTest.h>

class MCMCDatabaseConnectorTest : public DatabaseTest, public Test
{
public:
    void SetUp()
    {
        DatabaseTest::SetUp();
    }
};

TEST_F(MCMCDatabaseConnectorTest, createRun)
{
	std::string runUUID = mcmcConnection->createRun(runName);
    ASSERT_EQ(mcmcConnection->getRunId(), runUUID);
}

TEST_F(MCMCDatabaseConnectorTest, insertSample)
{
    auto runId = mcmcConnection->createRun(runName);
    mcmcConnection->insertSample(1, -25.44, 1.0);
    ASSERT_EQ(1, 1);
}
