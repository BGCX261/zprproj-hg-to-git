// author: Rafał Witowski

#include "Route.hpp"

namespace calc
{
    /** returns collection of cities in route */
    const Route::Cities& Route::getCities() const
    {
        return cities_;
    }

    /** returns collection of cities ids in route */
    const Route::CitiesIds& Route::getCitiesIds() const
    {
        return citiesIds_;
    }

    /** returns number of the cities in route */
    unsigned Route::getCitiesNumber() const
    {
        return cities_.size();
    }

    /** appends city to the route */    
    void Route::addCity(const City &city)
    {
        cities_.push_back(city);
        citiesIds_.push_back(city.getId());
    }    
        
} // namespace calc    
