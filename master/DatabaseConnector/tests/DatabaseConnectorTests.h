#pragma once
#include <DatabaseConnector.h>
#include <DatabaseTest.h>
#include "testingIncludes.h"

class DatabaseConnectorTest : public DatabaseTest {
public:
    std::shared_ptr<DatabaseConnector> dbConnection;
    void clearDatabase(){dbConnection.get()->execute(clearDatabaseQuery);}
    void SetUp() {
        DatabaseTest::SetUp();
        dbConnection.reset(
                new DatabaseConnector(hostName, userName, userPassword, database));
        clearDatabase();
    }
};

TEST_F(DatabaseConnectorTest, executeQuery) {
    std::stringstream selectQuery;
    selectQuery << "insert into samples values(NULL, 1, 3.5);";
    dbConnection->execute(selectQuery.str());
    ASSERT_EQ(1, 1);
}

TEST_F(DatabaseConnectorTest, executFetchQuery) {
    dbConnection->execute("delete from run");
    dbConnection->execute("delete from samples");
    dbConnection->execute("insert into samples values(14, 1, 3.5);");
    auto results = dbConnection->executeFetchQuery("select min(runId) from samples;");
    results->next();
    auto queryResult = results->getInt(1);
    ASSERT_EQ(queryResult, 1);
}
