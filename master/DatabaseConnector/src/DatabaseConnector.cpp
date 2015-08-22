#include "DatabaseConnector.h"
#include <sstream>

DatabaseConnector::DatabaseConnector(std::string hostName, std::string userName,
        std::string userPassword, std::string database) :
m_driver(get_driver_instance()) {
    m_connected = connect(hostName, userName, userPassword, database);
}

DatabaseConnector::~DatabaseConnector() {
}

bool DatabaseConnector::connect(const std::string hostName,
        const std::string userName, const std::string userPassword,
        const std::string database) {
    m_connection = m_driver->connect(hostName, userName, userPassword);
    std::stringstream useQuery; // Use the right database
    useQuery << "USE " << database;
    return execute(useQuery.str());
}

bool DatabaseConnector::execute(const std::string query) {
    sql::Statement* stmt = m_connection->createStatement();
    return stmt->execute(query);
}

std::shared_ptr<sql::ResultSet> DatabaseConnector::executeFetchQuery(std::string query) {
    sql::Statement *stmt = m_connection->createStatement();
    sql::ResultSet* result = stmt->executeQuery(query);
    std::shared_ptr<sql::ResultSet> resultPointer;
    resultPointer.reset(result);
    return resultPointer;
}

