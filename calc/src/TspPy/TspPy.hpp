//#define BOOST_PYTHON_STATIC_LIB
#ifndef CALC_TSP_PY_HPP
#define CALC_TSP_PY_HPP

#include <boost/python.hpp>
#include "../Tsp/Tsp.hpp"

namespace calc
{
    /** Wrapper for Tsp, creates Tsp from python route object */
    class TspPy
    {
        public:
            /** c-tor, creates tsp from python_route */        
            TspPy(const boost::python::object &python_route);
            
            /** returns Tsp::getResult() converted to python list */                         
            boost::python::list getResult() const;
            
            /** returns Tsp::getState() result */
            Tsp::State getState() const;
            
            /** calls solve on tsp */
            void solve();
            
            /** returns handle to Tsp object */
            PTsp getTsp() const;
            
        private:
            PTsp tspPtr_; // tsp object
            
            // converts python_city to City
            City getCity(const boost::python::object &python_city) const; 
            
            // Extracts cities from python_cities object and adds them to route
            void addCities(PRoute route, const boost::python::list &python_cities) const;
            
            // Creates route from python_route object 
            PRoute getRoute(const boost::python::object &python_route) const;       
    };
    
} // namespace calc

#endif // CALC_TSP_PY_HPP
