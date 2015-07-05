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

    ChainRunner()
    {
    }

    ChainRunner(
            std::unique_ptr<MCMCDatabaseConnector> connection,
            std::unique_ptr<Chain<paramType>> chain
            ) : m_connection(connector), m_chain(chain)
    {
    }

private:
    std::unique_ptr<MCMCDatabaseConnector> m_connection;
    std::unique_ptr<Chain<paramType>> m_chain;
};
