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
        typedef Route::CitiesIds Result;
        typedef boost::shared_ptr<Route::CitiesIds> PResult;            
        enum State { NONE, SOLVING, SOLVED };
        
        Tsp(PRoute route);
        
        void solve();
                
        const Result& getResult() const;
        State getState() const;
        
    private:

            
        const PRoute route_;
        State state_;
        PResult result_;        
        
        mutable boost::mutex stateMutex_;
        mutable boost::mutex resultMutex_;                  
        mutable boost::condition_variable resultCond_;        
        
        void setState(State state);   
};

#endif //TSP_HPP
