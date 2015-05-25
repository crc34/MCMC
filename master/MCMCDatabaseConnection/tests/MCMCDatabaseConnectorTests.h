#pragma once
#include <testingIncludes.h>
#include <MCMCDatabaseConnector.h>

TEST(MCMCDatabaseConnector, FullConstructor) {
    std::string hostName = "localhost";
    std::string userName = "user";
    std::string userPassword = "password";
    std::string database = "tmp";
    auto dbConnection =
            new MCMCDatabaseConnector(hostName, userName, userPassword, database);
    delete(dbConnection);
    ASSERT_EQ(1, 1);
}

TEST(MCMCDatabaseConnector, createRun) {
    std::string hostName = "localhost";
    std::string userName = "user";
    std::string userPassword = "password";
    std::string database = "tmp";
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
    ASSERT_EQ(runId, 1);
}




