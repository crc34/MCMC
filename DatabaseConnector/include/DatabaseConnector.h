
#pragma once
#include "mysql_connection.h"
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

        std::unique_ptr<sql::PreparedStatement> getPreparedStatement(
            const std::string preparedStatementString)
        {
            std::unique_ptr<sql::PreparedStatement> preparedStatement;
            preparedStatement.reset(
                m_connection->prepareStatement(preparedStatementString));
            return preparedStatement;
        }
        
    private:

        /*! connects to the input database**/
        bool connect(
                const std::string hostName,
                const std::string userName,
                const std::string userPassword,
                const std::string database);

        /*! driver object */
        sql::Driver* m_driver;

        /*! Connection object*/
        sql::Connection* m_connection;

        /*! indicates whether or not the database is connected*/
        bool m_connected;

        // Tests
        FRIEND_TEST(DatabaseConnectorTest, FullConstructor);
        FRIEND_TEST(DatabaseConnectorTest, executeQuery);
        FRIEND_TEST(DatabaseConnectorTest, executFetchQuery);
};
