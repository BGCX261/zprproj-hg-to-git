#ifndef TSP_HPP
#define TSP_HPP

#include <boost/shared_ptr.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/condition_variable.hpp>

#include "Route.hpp"

typedef boost::shared_ptr<Route> PRoute;

class Tsp
{
    public:
        typedef unsigned int TspId;
        typedef Route::CitiesIds Result;
        typedef boost::shared_ptr<Route::CitiesIds> PResult;            
        enum State { NONE, QUEUED, SOLVING, SOLVED };
        
        Tsp(PRoute route);
        
        void solve();
                
        const Result& getResult() const;
        
        void setId(TspId id);        
        void setState(State state); 
                  
        State getState() const;        
        TspId getId() const;
        
    private:           
        const PRoute route_;
        TspId id_;              
        State state_;
        PResult result_;  

        
        mutable boost::mutex stateMutex_;
        mutable boost::mutex resultMutex_;                  
        mutable boost::condition_variable resultCond_;
};

#endif //TSP_HPP
