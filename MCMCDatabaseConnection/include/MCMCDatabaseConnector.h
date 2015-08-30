#pragma once
#include <iostream>
#include <memory>
#include <DatabaseConnector.h>
#include <gtest/gtest_prod.h>
#include <boost/format.hpp>

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
        void insertSample(int runId, int iteration, double logPosterior,
            double theta);

    private:
        std::unique_ptr<DatabaseConnector> m_connection;
        std::string m_createRunQueryString =
             "insert into run values(NULL, \"%s\")";
        std::unique_ptr<boost::format> m_createRunQueryFormat;
        std::string m_selectRunIdQueryString =
             "select runId from run where runName =  \"%s\";";
        std::unique_ptr<boost::format> m_selectRunIdQueryFormat;
        std::string m_insertSamplesQueryString =
            "insert into samples values(%i, %i, %f, %f)";
        std::unique_ptr<boost::format> m_insertSamplesQueryFormat;
};
