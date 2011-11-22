#ifndef WLOGIC_HPP_INCLUDED
#define WLOGIC_HPP_INCLUDED

#include <boost/python.hpp>
#include "CLogic.hpp"

using namespace boost;

BOOST_PYTHON_MODULE(wlogic)
{
	python::class_<CLogic>("wlogic")
		.def("getInstance", &CLogic::getInstance, python::return_value_policy<python::reference_existing_object>())
		.staticmethod("getInstance")
		.def("revertLastMove", &CLogic::revertLastMove)
		.def("getLastMove", &CLogic::getLastMove, python::return_value_policy<python::reference_existing_object>())
		.def("getWorkingID", &CLogic::getWorkingID)
		.def("setWorkingID", &CLogic::setWorkingID)
		.def("pushWorkingPlayer", &CLogic::pushWorkingPlayer)
		.def("popWorkingPlayer", &CLogic::popWorkingPlayer)
		.def("getWorkingPlayer", &CLogic::getWorkingPlayer)
	  ;
}

#endif

