#pragma once
#include <DatabaseConnector.h>
#include <DatabaseTest.h>
#include "testingIncludes.h"

class DatabaseConnectorTest : public DatabaseTest {
public:
    std::shared_ptr<DatabaseConnector> dbConnection;
    void clearDatabase(){
        for (auto query : clearDatabaseQuery)
        {
            dbConnection.get()->execute(query);
        }   
    }
    void SetUp() {
        DatabaseTest::SetUp();
        dbConnection.reset(
                new DatabaseConnector(hostName, userName, userPassword, database));
        clearDatabase();
    }
};

TEST_F(DatabaseConnectorTest, executeQuery) {
    dbConnection->execute(insertQuery);
    ASSERT_EQ(1, 1);
}

TEST_F(DatabaseConnectorTest, executFetchQuery) {
    dbConnection->execute(insertQuery);
    auto results = dbConnection->executeFetchQuery(selectQuery);
    results->next();
    auto queryResult = results->getInt(1);
    ASSERT_EQ(queryResult, 1);
}
