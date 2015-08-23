
#pragma once
#include "mysql_connection.h"

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <gtest/gtest_prod.h>

/**
Interacts with a mysql database. 
 */
class DatabaseConnector
{
    public:
        DatabaseConnector() =  delete;
        ~DatabaseConnector();

        /*! Create a new connector and connects to the database. 
        *     \param hostName name of host.` 
        *     \param userName user name.` 
        *     \param userPassword password.` 
        *     \param database databaseName.`   
        **/ 
        DatabaseConnector(
            const std::string hostName,
            const std::string userName,
            const std::string userPassword,
            const std::string database);
        /*! execute the input query. Only use for query with no return values.
         *    \param query query string
         **/
        bool execute(const std::string query);

        /*! execute the input query. Use when you want results returned.
         *    \param query query string
         *    \return shared pointer to the result set.
         **/
        std::shared_ptr<sql::ResultSet> executeFetchQuery(std::string query);

        /** returns true if the connector is connected*/ 
        bool isConnected(){return m_connected;}
    private:
        bool connect(const std::string hostName, const std::string userName,
            const std::string userPassword, const std::string database);
        sql::Driver* m_driver;
        sql::Connection* m_connection;
        bool m_connected;
        FRIEND_TEST(DatabaseConnectorTest, FullConstructor);
        FRIEND_TEST(DatabaseConnectorTest, executeQuery);
        FRIEND_TEST(DatabaseConnectorTest, executFetchQuery);
};
