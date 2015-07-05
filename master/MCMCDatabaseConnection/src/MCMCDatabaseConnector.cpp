#include <iostream> 
#include <sstream>
#include <MCMCDatabaseConnector.h>

MCMCDatabaseConnector::MCMCDatabaseConnector(const std::string hostName,
            const std::string userName, const std::string userPassword,
            const std::string database)
{
    m_connection.reset(new DatabaseConnector(hostName, userName,
        userPassword, database));
    createRunQueryFormat.reset(new boost::format("insert into run values(NULL, \"%s\")"));
    selectRunIdQueryFormat.reset(new boost::format("select runId from run where runName =  \"%s\";"));
    insertSamplesQueryFormat.reset(new boost::format("insert into samples values(%i, %i, %f)"));
}

MCMCDatabaseConnector::~MCMCDatabaseConnector()
{

}

int MCMCDatabaseConnector::createRun(std::string runName)
{
    auto query = boost::str(*(createRunQueryFormat.get()) % runName);
    m_connection->execute(query);
    return getRunId(runName);
}

int MCMCDatabaseConnector::getRunId(std::string runName)
{
    boost::format createRunQueryFormat();
    auto query = boost::str(*(selectRunIdQueryFormat.get()) % runName);
    auto results = m_connection->executeFetchQuery(query);
    results->next();
    auto runId = results->getInt(1);
    return runId;
}

void MCMCDatabaseConnector::insertSample(int runId, int sampleNumber, double theta)
{
    auto query = boost::str(*(insertSamplesQueryFormat.get()) % runId % sampleNumber % theta);
    m_connection->execute(query);
}
