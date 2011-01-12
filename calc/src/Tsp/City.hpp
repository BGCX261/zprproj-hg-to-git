// author: Rafał Witowski

#ifndef CALC_CITY_HPP
#define CALC_CITY_HPP

#include <utility>
#include <cmath>

namespace calc
{
    typedef double Distance; // Distance beetween cities
    
    /** Single city */
    class City
    {
        public:
            typedef int CityId; /** City's identifier type */
            typedef int Coord;  /** City's coordinate type */
            
            /** Specifies new City at position (x, y) */
            City(CityId id, Coord x, Coord y) : id_(id), coords_(x, y) {}
            
            /** returns City identifier */   
            CityId getId() const { return id_; }
            
            /** returns x coordinate of city */
            Coord getX() const { return coords_.first; }
            
            /** returns y coordinate of city */                
            Coord getY() const { return coords_.second; }
            
            /** returns distance from this city to another one (dest_city), 
                calculated from these cities coordinates */
            Distance distance(const City &dest_city) const
            {
                Coord dx = getX() - dest_city.getX();
                Coord dy = getY() - dest_city.getY();
              
                return sqrt(static_cast<double>(dx*dx + dy*dy));
            }
            
        private:
            // x,y coordinates of the city
            typedef std::pair<Coord, Coord> Coords;          
        
            // identifier of a city
            CityId id_;
            
            // coordinates
            Coords coords_;
    };

} // namespace calc

#endif // CALC_CITY_HPP

