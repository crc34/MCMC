#include "DatabaseConnector.h"
#include <sstream>
DatabaseConnector::DatabaseConnector(){}
DatabaseConnector::DatabaseConnector(std::string hostName, std::string userName,
    std::string userPassword, std::string database) :
    driver(get_driver_instance())
{
}

void DatabaseConnector::connect(std::string hostName, std::string userName,
    std::string userPassword, std::string database)
{
    con = driver->connect(hostName, userName, userPassword);

    /* Use the right database*/
    std::stringstream useQuery;
    useQuery << "USE " << database;
    bool success = execute(useQuery.str());
}

bool DatabaseConnector::execute(std::string query)
{
    sql::Statement* stmt = con->createStatement();
    return stmt->execute(query);
}