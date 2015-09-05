#pragma once
#include <MCMCDatabaseConnector.h>
#include <Chain.h>
#include <gtest/gtest_prod.h>

template<typename paramType> class ChainRunner
{
    using proposalFunctionTemplate =
        std::function<std::shared_ptr<paramType> (const std::shared_ptr<paramType> currentVal)>;
    using logPosteriorFunctionTemplate =
        std::function<double(const std::shared_ptr<paramType> Theta)>;
public:
    ChainRunner();
    
    /** connection should already be established*/
    ChainRunner(std::shared_ptr<MCMCDatabaseConnector> connection,
            std::shared_ptr<Chain<paramType>> chain):
            m_chain(std::move(chain)), m_connection(std::move(connection))
    {


    }
 
    bool stepAndWrite(const int iteration, const bool flushPreparedStatement)
    {
        auto chain = m_chain.get();
        auto connection = m_connection.get();
        auto runId = m_connection->getRunId();
        chain->step();
        auto currentVal = chain->getCurrentTheta();
        auto currentLogPosterior = chain->getCurrentLogPosterior(); 
        connection->insertSample(iteration, currentLogPosterior, *currentVal,
            flushPreparedStatement);
    }

private:
    std::shared_ptr<MCMCDatabaseConnector> m_connection;
    std::shared_ptr<Chain<paramType>> m_chain;
    int m_runId;
    FRIEND_TEST(ChainRunnerTest, constructor);
};
