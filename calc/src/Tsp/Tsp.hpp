#ifndef CALC_TSP_HPP
#define CALC_TSP_HPP

#include <boost/shared_ptr.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/condition_variable.hpp>

#include "Route.hpp"
#include "TspException.hpp"


namespace calc
{
    typedef boost::shared_ptr<Route> PRoute;    
    
    /** Exception thrown when Tsp is created from empty route */    
    class TspBadRouteException : public TspException
    {
        public:
            TspBadRouteException() : TspException("Can't create tsp with no cities in route") {}
    };

    /** Traveling salesman problem class. Creates TSP from specified route and
     *  offers solving through TspGraph */
    class Tsp
    {
        public:
            typedef Route::CitiesIds Result; /* result type, collection of cities ids in proper order */
            typedef boost::shared_ptr<Route::CitiesIds> PResult;
            
            /** 
             *  Available states of traveling salesman problem
             *  NONE means that tsp was only created
             *  QUEUED means that tsp was added to queue for solving,
             *      but the solving method was not started yet           
             *  SOLVING means solving in progress
             *  SOLVED means that solving procedure has ended and there is a result available
             */
            enum State { NONE, QUEUED, SOLVING, SOLVED };
            
            /** Creates tsp from route */             
            Tsp(PRoute route);            
            
            /** 
             *  Returns result (approximated solution of TSP). 
             *  If it was not solved yet this method blocks until the result is ready
             */
            const Result& getResult() const;  
            
            /** Returns current state of tsp */                    
            State getState() const;                
            
            /** If state is NONE sets it to QUEUED, otherwise do nothing */                  
            void setQueued();
            
            /** Builds TspGraph and runs its optimize method. Updates the state of TSP */
            void solve();                           
            
        private:           
            const PRoute route_; // Route passed in c-tor, used when building graph
                       
            State state_; // Current tsp state
            
            PResult result_; // Ptr to result
            
            mutable boost::mutex mutex_; // Mutex to control access to state and result
            
            mutable boost::condition_variable solvedCond_;             
    };
    
    typedef boost::shared_ptr<Tsp> PTsp;    
        
} // namespace calc           


#endif // CALC_TSP_HPP
