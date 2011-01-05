#include <boost/python.hpp>

#include "TspPy/TspPy.hpp"
#include "TspPy/TspManagerPy.hpp"

using namespace boost::python;

BOOST_PYTHON_MODULE( calc )
{
	boost::python::enum_<calc::Tsp::State>("TspState")
		.value("NONE", calc::Tsp::NONE)
		.value("QUEUED", calc::Tsp::QUEUED)		
		.value("SOLVING", calc::Tsp::SOLVING)
		.value("SOLVED", calc::Tsp::SOLVED)
		.export_values();

	boost::python::class_<calc::TspPy>("Tsp", init<boost::python::object>())
		.def("solve", &calc::TspPy::solve)
		.def("getResult", &calc::TspPy::getResult)
		.def("getState", &calc::TspPy::getState);
		
	boost::python::class_<calc::TspManagerPy>("TspManager")
		.def("solve", &calc::TspManagerPy::solve);
}

