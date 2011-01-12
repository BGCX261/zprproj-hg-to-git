// author: Rafał Witowski

#ifndef CALC_ROUTE_HPP
#define CALC_ROUTE_HPP

#include <vector>

#include "City.hpp"

namespace calc
{
    /** Route containing cities */
    class Route
    {
        public:        
            typedef std::vector<City> Cities; /** Cities collection */
            typedef std::vector<City::CityId> CitiesIds; /** Collection of cites identifiers */
            
            /** returns collection of cities in route */
            const Cities& getCities() const;
                       
            /** returns collection of cities ids in route */
            const CitiesIds& getCitiesIds() const;            
            
            /** returns number of the cities in route */
            unsigned getCitiesNumber() const;
            
            /** appends city to the route */
            void addCity(const City &city);            
            
        private:
            CitiesIds citiesIds_; // identifiers of cities in route
            
            Cities cities_; // cities in route       
    };    
        
} // namespace calc        

#endif // CALC_ROUTE_HPP
