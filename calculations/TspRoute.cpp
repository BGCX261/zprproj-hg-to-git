#include "TspRoute.hpp"
#include "TspGraph.hpp"

TspRoute::TspRoute() :
    route_(new TspRoute::Route),
    state_(TspRoute::NONE)
{}
        
void TspRoute::addCity(PCity city)
{
    routeMutex_.lock();          
    route_->push_back(city);
    routeMutex_.unlock();
}

TspRoute::State TspRoute::getState() const
{
    boost::mutex::scoped_lock sl(stateMutex_);
    return state_;
}
             
const TspRoute::Route& TspRoute::getRoute() const
{
    boost::mutex::scoped_lock sl(routeMutex_);
    return *route_;
}

    
void TspRoute::optimize()
{
    boost::mutex::scoped_lock sl(routeMutex_);
    setState(OPTIMIZING);
    TspGraph tsp_graph(*route_);
    route_ = tsp_graph.optimizedRoute();
    setState(OPTIMIZED);
}

void TspRoute::setState(TspRoute::State state)
{
    stateMutex_.lock();
    state_ = state;
    stateMutex_.unlock();
}
