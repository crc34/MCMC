#pragma once
//#include <ChainTest.h>
#include <random>
#include <functional>
#include <memory>
#include <gtest/gtest_prod.h>
template<typename paramType> class Chain
{
    using proposalFunctionTemplate =
        std::function<std::shared_ptr<paramType> (const std::shared_ptr<paramType> currentVal)>;
    using logPosteriorFunctionTemplate =
        std::function<double(const std::shared_ptr<paramType> Theta)>;
public:

    Chain() = delete;

    Chain(
            proposalFunctionTemplate _proposalFunction,
            logPosteriorFunctionTemplate _logPosterior,
            std::shared_ptr<paramType> initialValue
            ) : m_proposalFunction(_proposalFunction),
    m_logPosterior(_logPosterior),
    m_currentTheta(initialValue)
    {
        m_currentLogPosterior = m_logPosterior(m_currentTheta);
    }

    /** iterates the markov chain according to MH*/
    void step();

    std::shared_ptr<paramType> getCurrentTheta() const;

    double getCurrentLogPosterior() const {return m_currentLogPosterior;}

private:

    /** returns true if this proposal is accepted */
    bool accept(const double logCurrent, const double logProposal) const;

    std::shared_ptr<paramType> m_currentTheta; // current state of chain
    double m_currentLogPosterior{-1}; // logPosterior of current state

    //updates proposedVal with a proposal
    proposalFunctionTemplate m_proposalFunction;

    /** returns the log posterior of Theta */
    logPosteriorFunctionTemplate m_logPosterior;

    FRIEND_TEST(ChainTest, AcceptFunction);
    FRIEND_TEST(ChainTest, testConvergence);
};
#include <Chain.inl>
