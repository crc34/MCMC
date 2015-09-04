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
        /** Gets a runId associated with a runName
            returns -1 if it doesn't exist*/
        int getRunId(std::string runName);
        /**
         * 
         * @param logPosterior log of the posterior
         * @param theta sampled value
         * @param flushPreparedStatement true if the insert sample
         * prepared statement should be flushed to the database.
         * @return void
         */
        void insertSample(double logPosterior,
            double theta, bool flushPreparedStatement);
        int getRunId(){return m_runId;}

    private:

        int m_runId{-1};
 
        std::unique_ptr<DatabaseConnector> m_connection;

        const std::string m_createRunQueryString{
             "insert into run values(NULL, \"%s\")"};
        std::unique_ptr<boost::format> m_createRunQueryFormat;
        const std::string m_selectRunIdQueryString{
             "select runId from run where runName =  \"%s\";"};
        std::unique_ptr<boost::format> m_selectRunIdQueryFormat;
        const std::string insertSamplePreparedStatementString{
            "insert into samples values(NULL, ?, ?, ?)"};
        std::unique_ptr<sql::PreparedStatement>  insertSamplePreparedStatement;
};
