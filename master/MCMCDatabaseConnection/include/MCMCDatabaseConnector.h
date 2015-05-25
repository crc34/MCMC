#pragma once
#include <iostream>
#include <memory>
#include <DatabaseConnector.h>

class MCMCDatabaseConnector
{
    public:
        MCMCDatabaseConnector() =  delete;
        ~MCMCDatabaseConnector();
        MCMCDatabaseConnector(const std::string hostName,
            const std::string userName, const std::string userPassword,
            const std::string database);
    private:
        std::unique_ptr<DatabaseConnector> m_connection;
};
