#include "Tsp.hpp"
#include "TspGraph.hpp"

Tsp::Tsp(PRoute route) :
    route_(route),
    id_(0),
    state_(NONE)
{}


void Tsp::solve()
{
    setState(SOLVING);
    
    route_->lock();        
    TspGraph tsp_graph(route_->getCities());
    result_ = tsp_graph.optimizeRoute();
    route_->unlock();
        
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


void Tsp::setId(TspId id)
{
    id_ = id;
}


void Tsp::setState(State state)
{
    stateMutex_.lock();
    state_ = state;
    stateMutex_.unlock();
}


Tsp::State Tsp::getState() const
{
    boost::mutex::scoped_lock lock(stateMutex_);
    return state_;
}


Tsp::TspId Tsp::getId() const
{
    return id_;
}

