
#pragma once
#include "mysql_connection.h"

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

class DatabaseConnector
{
    public:
        DatabaseConnector();
        DatabaseConnector(std::string hostName, std::string userName,
            std::string userPassword, std::string database);
        bool execute(std::string query);

    private:
        void connect(std::string hostName, std::string userName,
            std::string userPassword, std::string database);
        sql::Driver* driver;
        sql::Connection* con;
};