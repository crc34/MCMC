#include <iostream> 
#include <sstream>
#include <MCMCDatabaseConnector.h>
#include <bits/unique_ptr.h>

MCMCDatabaseConnector::MCMCDatabaseConnector(const std::string hostName,
            const std::string userName, const std::string userPassword,
            const std::string database)
{
    m_connection.reset(new DatabaseConnector(hostName, userName,
        userPassword, database));
    m_createRunQueryFormat.reset(new boost::format(m_createRunQueryString));
    m_selectRunIdQueryFormat.reset(new boost::format(m_selectRunIdQueryString));
    insertSamplePreparedStatement =
            m_connection->getPreparedStatement(insertSamplePreparedStatementString);
}

MCMCDatabaseConnector::~MCMCDatabaseConnector()
{

}

int MCMCDatabaseConnector::createRun(std::string runName)
{
    auto query = boost::str(*m_createRunQueryFormat % runName);
    m_connection->execute(query);
    m_runId = getRunId(runName); 
    return m_runId;
}

int MCMCDatabaseConnector::getRunId(std::string runName)
{
    boost::format createRunQueryFormat();
    auto query = boost::str(*m_selectRunIdQueryFormat % runName);
    auto results = m_connection->executeFetchQuery(query);
    results->next();
    auto runId = results->getInt(1);
    return runId;
}

/** inserts a sample*/
void MCMCDatabaseConnector::insertSample(double logPosterior, double theta, bool flushPreparedStatement)
{
    insertSamplePreparedStatement->setInt(1, m_runId);
    insertSamplePreparedStatement->setDouble(2, logPosterior);
    insertSamplePreparedStatement->setDouble(3, theta);
    insertSamplePreparedStatement->executeUpdate();
    if (flushPreparedStatement)
        insertSamplePreparedStatement->execute();
}
