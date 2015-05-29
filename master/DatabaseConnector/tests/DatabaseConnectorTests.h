#pragma once
#include <DatabaseConnector.h>
#include "testingIncludes.h"

namespace DatabaseConnectorTest{
std::string hostName = "localhost";
std::string userName = "user";
std::string userPassword = "password";
std::string database = "tmp";

TEST(DatabaseConnector, FullConstructor) {
    auto dbConnection =
            new DatabaseConnector(hostName, userName, userPassword, database);
    delete(dbConnection);
    ASSERT_EQ(1, 1);
}

TEST(DatabaseConnector, executeQuery) {
    auto dbConnection =
            new DatabaseConnector(hostName, userName, userPassword, database);
    std::stringstream selectQuery;
    selectQuery << "insert into samples values(NULL, 1, 3.5);";
    dbConnection->execute(selectQuery.str());
    delete(dbConnection);
    ASSERT_EQ(1, 1);
}

TEST(DatabaseConnector, executFetchQuery) {
    auto dbConnection =
            new DatabaseConnector(hostName, userName, userPassword, database);

    dbConnection->execute("delete from run");
    dbConnection->execute("delete from samples");
    dbConnection->execute("insert into samples values(14, 1, 3.5);");
    auto results = dbConnection->executeFetchQuery("select min(runId) from samples;");
    delete(dbConnection);
    results->next();
    auto queryResult = results->getInt(1);
    ASSERT_EQ(queryResult, 14);
}
}
