#pragma once
#include <testingIncludes.h>
#include "gmock/gmock.h"

class DatabaseTest : public Test
{
public:
	std::string hostName = "localhost";
	std::string userName = "user";
	std::string userPassword = "password";
	std::string database = "tmp";
};