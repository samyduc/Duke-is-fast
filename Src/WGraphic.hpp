///=============================================================================
///
/// \file           WGraphic.hpp
///
/// \date           Creation date:  24/02/2009
/// \date           Latest update:  08/08/2009
///
///	\author			Samy Duc, nobunaga.duc@gmail.com
///
/// \brief          Wrapper for Graphic module using Boost.
///
///=============================================================================


// Include guard
//#ifndef WGRAPHIC_HPP_INCLUDED
//#define WGRAPHIC_HPP_INCLUDED

#include <boost/python.hpp>
#include "CGraphic.hpp"
#include "GraphicEntity.hpp"
#include <string>

namespace python = boost::python;

BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(setPosition_overloads_graphic, CGraphic::setPosition, 2, 4)
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(setMove_overloads_graphic, CGraphic::setMove, 2, 4)

BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(setPosition_overloads_entity_graphic, GraphicEntity::setPosition, 1, 3)
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(setMove_overloads_entity_graphic, GraphicEntity::setMove, 1, 3)

BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(getBack, std::list<GraphicEntity*>::back, 3, 3)

BOOST_PYTHON_MODULE(wgraphic)
{
	python::class_<CGraphic>("wgraphic")
		.def("setAction", &CGraphic::setAction)
		.def("getInstance", &CGraphic::getInstance, python::return_value_policy<python::reference_existing_object>())
		.staticmethod("getInstance")
		.def("setPosition", (void(CGraphic::*)(int, const Point2d<float>&, std::string, float))0, setPosition_overloads_graphic())
		.def("setMove", (void(CGraphic::*)(int, const Point2d<float>&, std::string, float))0, setMove_overloads_graphic())
		.def("getPosition", &CGraphic::getPosition, python::return_value_policy<python::reference_existing_object>())
		.def("setRotation", &CGraphic::setRotation)
		.def("getWorkingID", &CGraphic::getWorkingID)
		.def("setView", &CGraphic::setView)
		.def("getCollisionList", &CGraphic::getCollisionList, python::return_value_policy<python::reference_existing_object>())
		;

	python::class_<GraphicEntity>("GraphicEntity", python::init<int, std::string>())
		.def("setAction", &GraphicEntity::setAction)
		.def("setPosition", (void(GraphicEntity::*)(const Point2d<float>&, std::string, float))0, setPosition_overloads_entity_graphic())
		.def("setMove", (void(GraphicEntity::*)(const Point2d<float>&, std::string, float))0, setMove_overloads_entity_graphic())
		.def("getPosition", &GraphicEntity::getPosition, python::return_value_policy<python::reference_existing_object>())
		.def("setRotation", &GraphicEntity::setRotation)
		.def("getID", &GraphicEntity::getID)
		;
}

//#endif