#pragma once

#include <DatabaseConnector.h>
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
        int createRun(const std::string runName);

        /**
         * 
         * @param logPosterior log of the posterior
         * @param theta sampled value
         * @param flushPreparedStatement true if the insert sample
         * prepared statement should be flushed to the database.
         * @return void
         */
        void insertSample(const int iteration, const double logPosterior,
            const double theta, const bool flushPreparedStatement);
        int getRunId() const {return m_runId;}

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
        
        /** Gets a runId associated with a runName
            returns -1 if it doesn't exist*/
        int getRunId(const std::string runName) const;
};
