#pragma once
#include <testingIncludes.h>
#include "gmock/gmock.h"

class DatabaseTest : public Test {
public:
    std::string hostName = "localhost";
    std::string userName = "user";
    std::string userPassword = "password";
    std::string database = "tmp";
    std::string runName = "firstRun";
    std::string clearDatabaseQuery = "delete from run; delete from samples;";
};