#ifndef CALC_TSP_HPP
#define CALC_TSP_HPP

#include <boost/shared_ptr.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/condition_variable.hpp>

#include "Route.hpp"

namespace calc
{

    typedef boost::shared_ptr<Route> PRoute;

    class Tsp
    {
        public:
            typedef Route::CitiesIds Result;
            typedef boost::shared_ptr<Route::CitiesIds> PResult; 
                       
            enum State { NONE, QUEUED, SOLVING, SOLVED };
            
            Tsp(PRoute route);
            
            const Result& getResult() const;  
                                
            State getState() const;                
                              
            void setState(State state);      
            
            void solve();                           
            
        private:           
            const PRoute route_;
                       
            State state_;
            
            PResult result_;  
            
            mutable boost::mutex mutex_;
            
            mutable boost::condition_variable solvedCond_;
            
            void setResult(PResult result);                          
    };
        
} // namespace calc           


#endif // CALC_TSP_HPP
