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
        // Creates a run and returns its id
        int createRun(std::string runName);
        // Gets a runId associated with a runName
        // returns -1 if it doesn't exist
        int getRunId(std::string runName);
    private:
        std::unique_ptr<DatabaseConnector> m_connection;
};
