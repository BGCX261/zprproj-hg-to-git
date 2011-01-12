#include "Tsp.hpp"
#include "TspGraph.hpp"
#include <iostream>

namespace calc
{
            
    Tsp::Tsp(PRoute route) :
        route_(route),
        state_(NONE),
        queuedNoSolve_(false)
    {
        /* Do not create tsp with no cities in route */
        if(route_->getCitiesNumber() == 0)
            throw TspBadRouteException();
    }

    /* Return current state */
    Tsp::State Tsp::getState() const
    {
        boost::mutex::scoped_lock lock(mutex_);
        return state_;
    }


    /* Return result */
    const Tsp::Result& Tsp::getResult() const
    {
        boost::mutex::scoped_lock lock(mutex_);
        
        // Block until tsp is solved
        while(state_ != SOLVED)
            solvedCond_.wait(lock);
  
        return *result_;
    }
    
    /* set state to queued */
    void Tsp::setQueued()
    {
        boost::mutex::scoped_lock lock(mutex_);
        if(state_ == NONE)
        {
            state_ = QUEUED;
            queuedNoSolve_ = true;
        }
    }

    /* solve tsp on graph */
    void Tsp::solve()
    {
        boost::mutex::scoped_lock lock(mutex_);
        if(state_ != NONE && !(state_ == QUEUED && queuedNoSolve_))
            return;
        
        queuedNoSolve_ = false;
        
        state_ = SOLVING;
        lock.unlock();
        
        
        TspGraph tsp_graph(route_->getCities()); // build graph
        PResult res = tsp_graph.optimizeRoute(); // get solution

        lock.lock();
        result_ = res;        
        state_ = SOLVED;
    }
        
} // namespace calc  



