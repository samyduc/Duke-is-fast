///=============================================================================
///
/// \file           WInput.cpp
///
/// \date           Creation date:  09/08/2008
/// \date           Latest update:  08/08/2009
///
/// \author         Benjamin Rimet, benjamin.rimet@gmail.com
///	\author			Samy Duc, nobunaga.duc@gmail.com
///
/// \brief          Python wrapper for input class.
///
///=============================================================================

#ifndef WINPUT_HPP_INCLUDED
#define WINPUT_HPP_INCLUDED

#include <boost/python.hpp>
#include "CInput.hpp"

using namespace boost;

BOOST_PYTHON_MODULE(winput)
{
  python::class_<CInput>("winput")
	  //.def("setAction", &CGraphic::setAction)
	  .def("getInstance", &CInput::getInstance, python::return_value_policy<python::reference_existing_object>())
	  .staticmethod("getInstance")
	  .def("getMousePosition", &CInput::getMousePosition, python::return_value_policy<python::reference_existing_object>())
	  ;
}

#endif

