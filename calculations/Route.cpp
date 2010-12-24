#include "Route.hpp"

void Route::addCity(const City &city)
{
    mutex_.lock_shared();
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

void Route::lock() const
{
    mutex_.lock_shared();
}

void Route::unlock() const
{
    mutex_.unlock_shared();
}
