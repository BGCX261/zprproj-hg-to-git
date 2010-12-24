#include "Tsp.hpp"
#include "TspGraph.hpp"

Tsp::Tsp(const Route &route) : route_(route)
{}

void Tsp::solve()
{
    setState(SOLVING);
    
    route_.lock();        
    TspGraph tsp_graph(route_.getCities());
    result_ = tsp_graph.optimizeRoute();
    route_.unlock();
        
    resultCond_.notify_all();
    setState(SOLVED);
}

const Tsp::Result& Tsp::getResult() const
{
    boost::mutex::scoped_lock lock(resultMutex_);
    if(getState() != SOLVED)
        resultCond_.wait(lock);
    return *result_;
}

Tsp::State Tsp::getState() const
{
    boost::mutex::scoped_lock lock(stateMutex_);
    return state_;
}

void Tsp::setState(State state)
{
    stateMutex_.lock();
    state_ = state;
    stateMutex_.unlock();
}
