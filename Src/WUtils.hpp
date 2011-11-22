///=============================================================================
///
/// \file           WUtils.cpp
///
/// \date           Creation date:  09/08/2008
/// \date           Latest update:  08/08/2009
///
/// \author         Benjamin Rimet, benjamin.rimet@gmail.com
///	\author			Samy Duc, nobunaga.duc@gmail.com
///
/// \brief          Python wrapper for utils class.
///
///=============================================================================

#include <boost/python.hpp>
#include "Point2d.hpp"

namespace python = boost::python;

BOOST_PYTHON_MODULE(utils)
{
	python::class_<Point2d<float>>("point2d", python::init<float, float>())
	.def("X", &Point2d<float>::X)
	.def("Y", &Point2d<float>::Y)
	.def("setX", &Point2d<float>::setX)
	.def("setY", &Point2d<float>::setY)
	;
}