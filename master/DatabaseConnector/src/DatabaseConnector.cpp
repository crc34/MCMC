#include "DatabaseConnector.h"
#include <sstream>

DatabaseConnector::DatabaseConnector(std::string hostName, std::string userName,
        std::string userPassword, std::string database) :
m_driver(get_driver_instance())
{
    connect(hostName, userName, userPassword, database);
}

DatabaseConnector::~DatabaseConnector()
{
}

void DatabaseConnector::connect(const std::string hostName,
        const std::string userName, const std::string userPassword,
        const std::string database)
{
    m_con = m_driver->connect(hostName, userName, userPassword);

    /* Use the right database*/
    std::stringstream useQuery;
    useQuery << "USE " << database;
    execute(useQuery.str());
}

void DatabaseConnector::execute(const std::string query)
{
    sql::Statement* stmt = m_con->createStatement();
    stmt->execute(query);
}

std::shared_ptr<sql::ResultSet> DatabaseConnector::executeFetchQuery(std::string query)
{
    sql::Statement *stmt = m_con->createStatement();
    sql::ResultSet* result = stmt->executeQuery(query);
    std::shared_ptr<sql::ResultSet> resultPointer;
    resultPointer.reset(result);
    return resultPointer;
}

