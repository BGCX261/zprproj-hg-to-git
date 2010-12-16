#ifndef CITY_HPP
#define CITY_HPP

#include <utility>
#include <cmath>

class City
{
    public:
        typedef int CityId;
        typedef int Coord;
        typedef std::pair<Coord, Coord> Coords;
        
        City(CityId id, Coord x, Coord y) : id_(id), coords_(x, y) {}
           
        CityId getId() const { return id_; }
        Coord getX() const { return coords_.first; }
        Coord getY() const { return coords_.second; }
        
        double distance(const City &dest_city) const
        {
            Coord dx = getX() - dest_city.getX();
            Coord dy = getY() - dest_city.getY();
            
            return sqrt(dx*dx + dy*dy);
        }
        
    private:        
    
        CityId id_;
        Coords coords_;
};

#endif //CITY_HPP

