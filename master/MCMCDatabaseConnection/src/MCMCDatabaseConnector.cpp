#include <iostream> 
#include <sstream>
#include <boost/format.hpp>
#include <MCMCDatabaseConnector.h>

MCMCDatabaseConnector::MCMCDatabaseConnector(const std::string hostName,
            const std::string userName, const std::string userPassword,
            const std::string database)
{
    m_connection.reset(new DatabaseConnector(hostName, userName,
        userPassword, database));
}

MCMCDatabaseConnector::~MCMCDatabaseConnector()
{

}

int MCMCDatabaseConnector::createRun(std::string runName)
{
    boost::format createRunQueryFormat("insert into run values(NULL, \"%s\")");
    auto query = boost::str(createRunQueryFormat % runName);
    m_connection->execute(query);
    return getRunId(runName);
}

int MCMCDatabaseConnector::getRunId(std::string runName)
{
    boost::format createRunQueryFormat("select runId from run where runName =  \"%s\";");
    auto query = boost::str(createRunQueryFormat % runName);
    auto results = m_connection->executeFetchQuery(query);
    results->next();
    auto runId = results->getInt(1);
    return runId;
}

void MCMCDatabaseConnector::insertSample(int runId, int sampleNumber, double theta)
{
    boost::format insertSamplesQueryFormat("insert into samples values(%i, %i, %f)");
    auto query = boost::str(insertSamplesQueryFormat % runId % sampleNumber % theta);
    m_connection->execute(query);
}





