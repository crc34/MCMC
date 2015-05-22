
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
        ~DatabaseConnector();
        DatabaseConnector(const std::string hostName,
            const std::string userName, const std::string userPassword,
            const std::string database);
        bool execute(const std::string query);

    private:
        void connect(const std::string hostName, const std::string userName,
            const std::string userPassword, const std::string database);
        sql::Driver* driver;
        sql::Connection* con;
};