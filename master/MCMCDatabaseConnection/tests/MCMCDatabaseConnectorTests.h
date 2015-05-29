#pragma once
#include <testingIncludes.h>
#include <MCMCDatabaseConnector.h>

const std::string hostName = "localhost";
const std::string userName = "user";
const std::string userPassword = "password";
const std::string database = "tmp";
 


TEST(MCMCDatabaseConnector, FullConstructor) {
   auto dbConnection =
            new MCMCDatabaseConnector(hostName, userName, userPassword, database);
    delete(dbConnection);
    ASSERT_EQ(1, 1);
}

TEST(MCMCDatabaseConnector, createRun) {
    auto mcmcConnection =
            new MCMCDatabaseConnector(hostName, userName, userPassword, database);
    auto dbConnection =
            new DatabaseConnector(hostName, userName, userPassword, database);

    dbConnection->execute("delete from run");
    dbConnection->execute("delete from samples");

    std::string runName = "firstRun";
    int runId = mcmcConnection->createRun(runName);

    delete(mcmcConnection);
    delete(dbConnection);
    ASSERT_NE(runId, -1);
}

TEST(MCMCDatabaseConnector, insertSample) {
    auto mcmcConnection =
            new MCMCDatabaseConnector(hostName, userName, userPassword, database);
    auto dbConnection =
            new DatabaseConnector(hostName, userName, userPassword, database);

    dbConnection->execute("delete from run");
    dbConnection->execute("delete from samples");

    std::string runName = "firstRun";
    int runId = mcmcConnection->createRun(runName);

    mcmcConnection->insertSample(runId, 1, 1.0);


    delete(mcmcConnection);
    delete(dbConnection);
    ASSERT_NE(runId, -1);
}

