#pragma once
#include "gmock/gmock.h"
#include <DatabaseConnector.h>

class DatabaseTest
{
public:
    const std::string hostName = "localhost";
    const std::string userName = "user";
    const std::string userPassword = "password";
    const std::string database = "tmp";
    const std::string runName = "firstRun";
    const std::vector<std::string> clearDatabaseQuery =
        {"delete from samples;", "delete from run;"};
    const std::string insertQuery =
        "insert into samples values(NULL, 1, -3.44, 3.5);";
    const std::string selectQuery =
        "select count(*) from samples where Theta=3.5;";
    std::shared_ptr<DatabaseConnector> dbConnection;
    std::shared_ptr<MCMCDatabaseConnector> mcmcConnection;

    void clearDatabase()
    {
        for (auto query : clearDatabaseQuery)
        {
            dbConnection.get()->execute(query);
        }
    }
    void SetUp()
    {
        dbConnection.reset(
                new DatabaseConnector(
                    hostName, userName, userPassword, database));
        mcmcConnection.reset(
                new MCMCDatabaseConnector(
                hostName, userName, userPassword, database));
        clearDatabase();
    }
};
