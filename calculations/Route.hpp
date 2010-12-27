#ifndef ROUTE_HPP
#define ROUTE_HPP

#include <vector>

#include <boost/thread/shared_mutex.hpp>

#include "City.hpp"

class Route
{
    public:        
        typedef std::vector<City> Cities;
        typedef std::vector<City::CityId> CitiesIds;          
        
        const Cities& getCities() const;
        const CitiesIds& getCitiesIds() const;
        
        void addCity(const City &city);
                                      
        void lock() const;
        void unlock() const;
        
    private:
        CitiesIds citiesIds_; 
        Cities cities_;
        
        mutable boost::shared_mutex mutex_;
};

#endif //ROUTE_HPP
