#pragma once
#include <MCMCDatabaseConnector.h>
#include <DatabaseConnectorTests.h>
class MCMCDatabaseConnectorTest : public DatabaseConnectorTest
{
    public:
    std::shared_ptr<MCMCDatabaseConnector> mcmcConnection;
    void SetUp()
    {
        DatabaseConnectorTest::SetUp();
        mcmcConnection.reset(
            new MCMCDatabaseConnector(
                hostName, userName, userPassword, database));
    }
};

TEST_F(MCMCDatabaseConnectorTest, createRun) {
    int runId = mcmcConnection.get()->createRun(runName);
    ASSERT_NE(runId, -1);
}

TEST_F(MCMCDatabaseConnectorTest, insertSample) {
    int runId = mcmcConnection->createRun(runName);
    mcmcConnection->insertSample(runId, 1, 1.0);
    ASSERT_NE(runId, -1);
}
