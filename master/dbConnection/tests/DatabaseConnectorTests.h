#pragma once
#include <DatabaseConnector.h>
#include <math.h>
#include <limits>
#include <gtest/gtest.h>
#include <cstddef>
#include <iostream>

TEST(DatabaseConnector, DefaultConstructor)
{
    auto dbConnection = new DatabaseConnector();
    delete(dbConnection);
    ASSERT_EQ(1, 1);
}

TEST(DatabaseConnector, FullConstructor)
{
    std::string hostName = "localhost";
    std::string userName = "user";
    std::string userPassword = "password";
    std::string database = "tmp";
    auto dbConnection =
        new DatabaseConnector(hostName, userName, userPassword, database);
    delete(dbConnection);
    ASSERT_EQ(1, 1);
}

TEST(DatabaseConnector, executeQuery)
{
    std::string hostName = "localhost";
    std::string userName = "user";
    std::string userPassword = "password";
    std::string database = "tmp";
    auto dbConnection =
        new DatabaseConnector(hostName, userName, userPassword, database);
    std::stringstream useQuery;
    useQuery << "insert into samples values(NULL, 1, 3.5);";
    dbConnection->execute(useQuery.str());
    delete(dbConnection);
    ASSERT_EQ(1, 1);
}