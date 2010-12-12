#ifndef CITYLIST_HPP
#define CITYLIST_HPP

#include <vector>
#include <cmath>
#include <numeric>
#include <functional>

#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>

#include "City.hpp"

typedef boost::shared_ptr<City> PCity;

class CityList
{
    public:
        typedef std::vector<PCity> Cities;
             
        void addCity(const PCity &city) { cities_.push_back(city); }
        
        int getSize() const { return cities_.size(); }
        
        const Cities& getCities() const { return cities_; }
        
        double getLength() const
        {
            double loop_val = 0.0;
            if(!cities_.empty())
                distance(cities_.back(), cities_.front());
                
            return std::inner_product(  cities_.begin(), cities_.end() - 1,
                cities_.begin() + 1, loop_val, std::plus<double>(),
                boost::bind(&CityList::distance, this, _1, _2));
        }
        
    private:
    
        double distance(const PCity &c1, const PCity &c2) const
        {   
            return c1->distance(*c2);
        }
            
        Cities cities_;
        
};

#endif //CITYLIST_HPP
