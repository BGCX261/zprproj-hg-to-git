#include "Route.hpp"

namespace calc
{
    
    void Route::addCity(const City &city)
    {
        cities_.push_back(city);
        citiesIds_.push_back(city.getId());
    }


    const Route::Cities& Route::getCities() const
    {
        return cities_;
    }


    const Route::CitiesIds& Route::getCitiesIds() const
    {
        return citiesIds_;
    }


    unsigned Route::getCitiesNumber() const
    {
        return cities_.size();
    }
        
} // namespace calc    
