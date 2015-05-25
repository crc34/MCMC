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

