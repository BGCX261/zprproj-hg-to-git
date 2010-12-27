#include <boost/python.hpp>

#include "TspPy.hpp"

using namespace boost::python;

BOOST_PYTHON_MODULE( calc )
{

	boost::python::enum_<Tsp::State>("TspState")
		.value("NONE",Tsp::NONE)
		.value("SOLVING",Tsp::SOLVING)
		.value("SOLVED",Tsp::SOLVED)
		.export_values();

	boost::python::class_<TspPy>("Tsp", init<boost::python::object>())
		.def("solve", &TspPy::solve )
		.def("getResult", &TspPy::getResult )
		.def("getState", &TspPy::getState )		
		;
}

