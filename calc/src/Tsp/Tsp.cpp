#include "Tsp.hpp"
#include "TspGraph.hpp"

namespace calc
{
            
    Tsp::Tsp(PRoute route) :
        route_(route),
        state_(NONE)
    {}


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
            throw "Tsp state is NONE";
        }
        else 
        {
            while(state_ != SOLVED)
                solvedCond_.wait(lock);
        }
                   
        return *result_;
    }


    void Tsp::setState(State state)
    {
        boost::mutex::scoped_lock lock(mutex_);
        state_ = state;
    }


    void Tsp::solve()
    {
        mutex_.lock();
        state_ = SOLVING;
        mutex_.unlock();
        
        TspGraph tsp_graph(route_->getCities());
        PResult res = tsp_graph.optimizeRoute();
        
        mutex_.lock();
        result_ = res;        
        state_ = SOLVED;
        mutex_.unlock();
    }
        
} // namespace calc  


