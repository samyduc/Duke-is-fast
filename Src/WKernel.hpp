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
/// \brief          Python wrapper for kernel class.
///
///=============================================================================

#include <boost/python.hpp>
#include "CKernel.hpp"

namespace python = boost::python;

BOOST_PYTHON_MODULE(kernel)
{
  python::class_<CKernel>("kernel")
	  	.def("uniqueID", &CKernel::uniqueID)
        .staticmethod("uniqueID")
		.def("addEntity", &CKernel::addEntity)
        .staticmethod("addEntity")
		.def("removeEntity", &CKernel::removeEntity)
        .staticmethod("removeEntity")
		.def("loadMap", &CKernel::loadMap)
        .staticmethod("loadMap")
	  ;
}