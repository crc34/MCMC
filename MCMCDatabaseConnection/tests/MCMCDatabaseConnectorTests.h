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
    int runId = mcmcConnection.get()->createRun(runName);
    ASSERT_NE(runId, -1);
}

TEST_F(MCMCDatabaseConnectorTest, insertSample)
{
    int runId = mcmcConnection->createRun(runName);
    mcmcConnection->insertSample(runId, 1, -25.44, 1.0);
    ASSERT_NE(runId, -1);
}
