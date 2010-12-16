#ifndef TSPROUTE_HPP
#define TSPROUTE_HPP

#include <vector>
#include <boost/shared_ptr.hpp>
#include <boost/thread/mutex.hpp>
#include "City.hpp"


typedef boost::shared_ptr<City> PCity;

class TspRoute
{
    public:
        typedef std::vector<PCity> Route;
        typedef boost::shared_ptr<Route> PRoute;
          
        enum State { NONE, OPTIMIZING, OPTIMIZED };
                
        
        TspRoute();
        
        void addCity(PCity city);
               
        State getState() const;
        
        const Route& getRoute() const;
        
        void optimize();
        
    private:

        PRoute route_;
        State state_;
        
        mutable boost::mutex stateMutex_;
        mutable boost::mutex routeMutex_;
        
        void setState(State state);
};




#endif //TSPROUTE_HPP
