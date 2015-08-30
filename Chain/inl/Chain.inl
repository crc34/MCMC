template<typename paramType>
void Chain<paramType>::step()
{
    auto proposal = m_proposalFunction(m_currentTheta);
    double proposalLogPosterior = m_logPosterior(proposal);
    if (accept(m_currentLogPosterior, proposalLogPosterior))
    {
        m_currentLogPosterior = proposalLogPosterior;
        m_currentTheta = proposal;
    }
}

template<typename paramType>
bool Chain<paramType>::accept(const double logCurrent,
        const double logProposal)
{
    auto rnd =
            static_cast<double> (rand()) / static_cast<double> (RAND_MAX);
    return std::log(rnd) < logProposal - logCurrent;
}

template<typename paramType>
std::shared_ptr<paramType> Chain<paramType>::getCurrentTheta()
{
    return m_currentTheta;
}
