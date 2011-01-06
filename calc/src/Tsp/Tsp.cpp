#include "Tsp.hpp"
#include "TspGraph.hpp"

namespace calc
{
            
    Tsp::Tsp(PRoute route) :
        route_(route),
        state_(NONE)
    {
        if(route_->getCitiesNumber() == 0)
            throw TspBadRouteException();
    }


    Tsp::State Tsp::getState() const
    {
        boost::mutex::scoped_lock lock(mutex_);
        return state_;
    }


    const Tsp::Result& Tsp::getResult() const
    {
        boost::mutex::scoped_lock lock(mutex_);
        
        if(state_ == NONE)
        {
            throw TspNoResultException();
        }
        else
        { 
            while(state_ != SOLVED)
                solvedCond_.wait(lock);
        }
                   
        return *result_;
    }
    
    
    void Tsp::setQueued()
    {
        boost::mutex::scoped_lock lock(mutex_);
        if(state_ == NONE)
            state_ = QUEUED;
    }


    void Tsp::solve()
    {
        boost::mutex::scoped_lock lock(mutex_);
        if(state_ != NONE)
            return;
        state_ = SOLVING;
        lock.unlock();
        
        TspGraph tsp_graph(route_->getCities());
        PResult res = tsp_graph.optimizeRoute();
        
        lock.lock();
        result_ = res;        
        state_ = SOLVED;
    }
        
} // namespace calc  



