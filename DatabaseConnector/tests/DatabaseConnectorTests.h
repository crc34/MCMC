#pragma once
#include <DatabaseTest.h>

class DatabaseConnectorTest : public DatabaseTest, public Test
{
public:
    void SetUp()
    {
        DatabaseTest::SetUp();
    }
};

TEST_F(DatabaseConnectorTest, executeQuery)
{
    dbConnection->execute(insertQuery);
    ASSERT_EQ(1, 1);
}

TEST_F(DatabaseConnectorTest, executFetchQuery)
{
    dbConnection->execute(insertQuery);
    auto results = dbConnection->executeFetchQuery(selectQuery);
    results->next();
    auto queryResult = results->getInt(1);
    ASSERT_EQ(queryResult, 1);
}
