#pragma once
#include <random>
#include <memory>
#include <iostream>

template<typename paramType> class Chain {
using proposalFunctionTemplate =  std::function<std::shared_ptr<paramType> (const std::shared_ptr<paramType> currentVal)> ;
using logPosteriorFunctionTemplate = std::function<double(const std::shared_ptr<paramType> Theta)>;
public:

    Chain() {
    }

    Chain(
            proposalFunctionTemplate _proposalFunction,
            logPosteriorFunctionTemplate _logPosterior,
            std::shared_ptr<paramType> initialValue
            ) : proposalFunction(_proposalFunction),
    logPosterior(_logPosterior) {
        currentTheta = initialValue;
        currentLogPosterior = logPosterior(currentTheta);
    }

    /** returns true if this proposal is accepted */
    bool accept(const double logCurrent, const double logProposal) {
        std::uniform_real_distribution<> dis(0, 1);
        auto rnd = dis(generator);
        return std::log(rnd) < logProposal - logCurrent;
    }

    /** updates proposedVal with a proposal */
    proposalFunctionTemplate proposalFunction;
   
    /** returns the log posterior of Theta */
    logPosteriorFunctionTemplate logPosterior;

    /** iterates the markov chain according to MH and returns true if the proposal was accepted */
    void step() {
        auto proposal = proposalFunction(currentTheta);
        double proposalLogPosterior = logPosterior(proposal);
        if (accept(currentLogPosterior, proposalLogPosterior)) {
            currentLogPosterior = proposalLogPosterior;
            currentTheta = proposal;
        }
    }
    std::default_random_engine generator;
    std::shared_ptr<paramType> currentTheta; // current state of chain
    double currentLogPosterior = -1; // logPosterior of current state
};
