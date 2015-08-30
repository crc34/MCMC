#include <iostream> 
#include <sstream>
#include <MCMCDatabaseConnector.h>

MCMCDatabaseConnector::MCMCDatabaseConnector(const std::string hostName,
            const std::string userName, const std::string userPassword,
            const std::string database)
{
    m_connection.reset(new DatabaseConnector(hostName, userName,
        userPassword, database));
    m_createRunQueryFormat.reset(new boost::format(m_createRunQueryString));
    m_selectRunIdQueryFormat.reset(new boost::format(m_selectRunIdQueryString));
    m_insertSamplesQueryFormat.reset(new boost::format(m_insertSamplesQueryString));
}

MCMCDatabaseConnector::~MCMCDatabaseConnector()
{

}

int MCMCDatabaseConnector::createRun(std::string runName)
{
    auto query = boost::str(*(m_createRunQueryFormat.get()) % runName);
    m_connection->execute(query);
    return getRunId(runName);
}

int MCMCDatabaseConnector::getRunId(std::string runName)
{
    boost::format createRunQueryFormat();
    auto query = boost::str(*(m_selectRunIdQueryFormat.get()) % runName);
    auto results = m_connection->executeFetchQuery(query);
    results->next();
    auto runId = results->getInt(1);
    return runId;
}

/** inserts a sample*/
void MCMCDatabaseConnector::insertSample(int runId, int sampleNumber,
        double logPosterior, double theta)
{
    auto query = boost::str(*(m_insertSamplesQueryFormat.get()) % runId
        % sampleNumber % logPosterior % theta);
    m_connection->execute(query);
}
