
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


