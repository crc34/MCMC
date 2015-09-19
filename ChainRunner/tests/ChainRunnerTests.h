#pragma once
#include <ChainRunner.h>
#include <DatabaseTest.h>
#include "GlobalDefines.h"
#include "gmock/gmock.h"
#include <globals.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include <Chain.h>
#include "gmock/gmock.h"
#include "Chain.h"

using namespace ::testing;
class ChainRunnerTest : public Test
{
public:

    const int m_nSamples = 100000000;
    
    const std::vector<std::string> clearDatabaseQuery =
        {"delete from samples;", "delete from run;"};
        
    const std::string hostName = "localhost";
    const std::string userName = "user";
    const std::string userPassword = "password";
    const std::string database = "tmp";
    const std::string runName = "firstRun";
    std::shared_ptr<MCMCDatabaseConnector> m_mcmcConnection;

    using paramType = double;
    using proposalFunctionTemplate =
            std::function<std::shared_ptr<paramType> (
            const std::shared_ptr<paramType> currentVal)>;
    using logPosteriorFunctionTemplate =
            std::function<double(const std::shared_ptr<paramType> Theta)>;
    double tolerance = 0.001;
    double _initialValue = 44;
    std::shared_ptr<double> initialValue;
    double trueMean = 0;
    double trueVariance = 1;
    std::unique_ptr<gsl_rng> r;
    const gsl_rng_type* T = gsl_rng_default;

    proposalFunctionTemplate proposalFunction;
    logPosteriorFunctionTemplate logPosterior;
    std::shared_ptr<Chain<double>> m_chain;
    
    std::unique_ptr<ChainRunner<double>> m_chainRunner;

    void clearDatabase()
    {
        for (auto query : clearDatabaseQuery)
        {
            m_mcmcConnection->executeQuery(query);
        }
    }
    
    void SetUp()
    {
        m_mcmcConnection.reset(
                new MCMCDatabaseConnector(
                hostName, userName, userPassword, database));
                gsl_rng_env_setup();
        r.reset(gsl_rng_alloc(T));
        clearDatabase();
        proposalFunction = [this](std::shared_ptr<double> Theta) {
            double draw = *Theta + 1.5*sqrt(trueVariance)*gsl_ran_gaussian_ziggurat(r.get(), 1);
            std::shared_ptr<double> proposal(new double(draw));
            return proposal;
        };

        logPosterior = [&](std::shared_ptr<double> Theta) {
            double val = *Theta - trueMean;
            val = -0.5 * val * val / trueVariance;
            return val;
        };
        initialValue.reset(new double(_initialValue));
        m_chain.reset(
                new Chain<double>(proposalFunction, logPosterior, initialValue));
        m_chainRunner.reset(
        new ChainRunner<double>(m_mcmcConnection, m_chain)
        );
    }
};

TEST_F(ChainRunnerTest, RunChain)
{
    for (int i = 0; i < m_nSamples; i++)
    {
        m_chainRunner->stepAndWrite(i);
    }
 
    const std::string firstMomentQuery{
                        "select sum(theta), sum(theta*theta) from samples"};

    auto result = m_mcmcConnection->executeFetchQuery(firstMomentQuery);
    result->next();
    auto mean = result->getDouble(1)/m_nSamples;
    auto secondMoment = result->getDouble(2)/m_nSamples;
    auto variance = secondMoment - std::pow(mean, 2);
    
    std::cout << "mean = " << mean << std::endl;
    std::cout << "variance = " << variance << std::endl;
    
}
