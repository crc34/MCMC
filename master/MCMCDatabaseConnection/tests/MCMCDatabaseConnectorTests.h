#pragma once
#include <MCMCDatabaseConnector.h>

class MCMCDatabaseConnectorTest : public DatabaseTest
{
    public:
    std::string runName = "firstRun";
    std::string clearDatabaseQuery = "delete from run; delete from samples;";
    std::shared_ptr<DatabaseConnector> dbConnection;
    std::shared_ptr<MCMCDatabaseConnector> mcmcConnection;
    void clearDatabase(){dbConnection.get()->execute(clearDatabaseQuery);}
    void SetUp()
    {
        DatabaseTest::SetUp();
        dbConnection.reset(
        new DatabaseConnector(hostName, userName, userPassword, database));
        mcmcConnection.reset(
            new MCMCDatabaseConnector(
                hostName, userName, userPassword, database));
        clearDatabase();
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
