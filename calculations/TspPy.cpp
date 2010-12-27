#include "TspPy.hpp"

       
TspPy::TspPy(const boost::python::object &python_route) :
    tspPtr_(new Tsp(getRoute(python_route)))
{}

TspPy::TspPy(PTsp tsp_ptr) :
    tspPtr_(tsp_ptr)
{}

 
boost::python::list TspPy::getResult() const
{
	const Tsp::Result &result = tspPtr_->getResult();
    boost::python::list python_result;
	for(Tsp::Result::const_iterator i = result.begin(); i != result.end(); ++i)
		python_result.append(*i);
		
    return python_result;
}

Tsp::TspId TspPy::getId() const
{
    return tspPtr_->getId();
}


Tsp::State TspPy::getState() const
{
    return tspPtr_->getState();
}

void TspPy::solve()
{
    tspPtr_->solve();
}

PTsp TspPy::getTsp() const
{
    return tspPtr_;
}


City TspPy::getCity(const boost::python::object &python_city) const
{
    using namespace boost::python;
    
    return City(extract<City::CityId>(python_city.attr("id")),
                extract<City::Coord> (python_city.attr("xcoord")),
                extract<City::Coord> (python_city.attr("ycoord")));
}


void TspPy::addCities(PRoute route, const boost::python::list &python_cities) const
{
	for(int i = 0; i < boost::python::len(python_cities); ++i)
		route->addCity(getCity(python_cities[i]));
}    


PRoute TspPy::getRoute(const boost::python::object &python_route) const
{
    PRoute route(new Route);
    boost::python::object many_related_manager = python_route.attr("cities");
    boost::python::list python_cities = static_cast<boost::python::list>(many_related_manager.attr("all")());
    addCities(route, python_cities);
    return route;
}         

