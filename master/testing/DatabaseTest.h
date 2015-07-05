#pragma once
#include <testingIncludes.h>
#include "gmock/gmock.h"

class DatabaseTest : public Test {
public:
    const std::string hostName = "localhost";
    const std::string userName = "user";
    const std::string userPassword = "password";
    const std::string database = "tmp";
    const std::string runName = "firstRun";
    const std::vector<std::string> clearDatabaseQuery = {"delete from samples;", "delete from run;"};
    const std::string insertQuery = "insert into samples values(NULL, 1, 3.5);";
    const std::string selectQuery = "select count(*) from samples where Theta=3.5;";
};