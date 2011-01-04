#ifndef CALC_TSP_PY_HPP
#define CALC_TSP_PY_HPP

#include <boost/python.hpp>
#include "Tsp.hpp"
#include "TspManager.hpp"

namespace calc
{

    class TspPy
    {
        public:        
            TspPy(const boost::python::object &python_route);
            TspPy(PTsp tsp_ptr);        
                          
            boost::python::list getResult() const;
            
            Tsp::TspId getId() const;
            Tsp::State getState() const;
            
            void solve();
            PTsp getTsp() const;
            
        private:
            PTsp tspPtr_;
            
            City getCity(const boost::python::object &python_city) const;
            void addCities(PRoute route, const boost::python::list &python_cities) const; 
            PRoute getRoute(const boost::python::object &python_route) const;       
    };
    
} // namespace calc

#endif // CALC_TSP_PY_HPP
