#include "DatabaseConnector.h"
#include <sstream>
DatabaseConnector::DatabaseConnector(){}
DatabaseConnector::DatabaseConnector(std::string hostName, std::string userName,
    std::string userPassword, std::string database) :
    driver(get_driver_instance())
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
    con = driver->connect(hostName, userName, userPassword);

    /* Use the right database*/
    std::stringstream useQuery;
    useQuery << "USE " << database;
    execute(useQuery.str());
}

void DatabaseConnector::execute(const std::string query)
{
    sql::Statement* stmt = con->createStatement();
    stmt->execute(query);
}