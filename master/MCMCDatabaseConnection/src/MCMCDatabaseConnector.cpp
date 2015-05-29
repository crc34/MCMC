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
    boost::format queryFormat("Entity_%s");
    auto query = boost::str(queryFormat % runName);
    m_connection->execute(query);
    return -1;
}
