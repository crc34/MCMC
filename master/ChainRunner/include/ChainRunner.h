#pragma once
#include <random>
#include <memory>
#include <iostream>
#include <MCMCDatabaseConnector.h>
#include <Chain.h>

template<typename paramType> class ChainRunner
{
    using proposalFunctionTemplate = std::function<std::shared_ptr<paramType> (const std::shared_ptr<paramType> currentVal)>;
    using logPosteriorFunctionTemplate = std::function<double(const std::shared_ptr<paramType> Theta)>;
public:
    ChainRunner() = delete;
    ChainRunner(std::shared_ptr<MCMCDatabaseConnector> connection,
            std::shared_ptr<Chain<paramType>> chain) :
            m_chain(chain), m_connection(connection){}
private:
    std::shared_ptr<MCMCDatabaseConnector> m_connection;
    std::shared_ptr<Chain<paramType>> m_chain;
};
