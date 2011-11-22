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