///=============================================================================
///
/// \file           LogicEntity.cpp
///
///
/// \author         Samy Duc, nobunaga.duc@gmail.com
///
/// \brief          Handle internal logic entity state
///
///=============================================================================

#include "LogicEntity.hpp"

// defined in CollisionBox
#define DEG_TO_RAD 0.017453f
#define RAD_TO_DEG 57.2957f
#define PI 3.1415926f 
#define LOGIC_S 0.016666f //60 Hz

LogicEntity::LogicEntity(int id, std::string type) : Entity(id, type)
{
	Entity::setAction("default");

	// default
	m_descriptor.hp = 0;
	m_descriptor.armor = 0;
	m_descriptor.velocity = 0.f;

	m_collide = false;
	m_updated = true;

	// settings
	parseEntity();
}

LogicEntity::~LogicEntity()
{

}

bool LogicEntity::update()
{
	CKernel::logic()->setWorkingID(Entity::getID());
	return CKernel::input()->doEntity(Entity::getType(), "update");
}

void LogicEntity::revertLastMove()
{
	m_move.setX(-m_move.X());
	m_move.setY(-m_move.Y());
	CKernel::graphic()->setMove(m_id, m_move);
}

Point2d<float> *LogicEntity::getLastMove()
{
	return &m_move;
}

bool LogicEntity::getCollide()
{
	return m_collide;
}

void LogicEntity::parseEntity()
{
	TiXmlDocument doc(Entity::getEntityFileName());
	TiXmlElement *elem_temp = NULL;

	if(doc.LoadFile())
	{
		TiXmlHandle hdl(&doc);
		// constant string must be replaced with module name
		TiXmlElement *element = hdl.FirstChildElement().FirstChildElement("logic").Element();

		if(element)
		{
				elem_temp = element->FirstChildElement("hp");
				if(elem_temp)
				{
					elem_temp->QueryIntAttribute("value", &m_descriptor.hp);
				}
				elem_temp = element->FirstChildElement("armor");
				if(elem_temp)
				{
					elem_temp->QueryIntAttribute("value", &m_descriptor.armor);
				}
				elem_temp = element->FirstChildElement("velocity");
				if(elem_temp)
				{
					elem_temp->QueryFloatAttribute("value", &m_descriptor.velocity);
				}
				elem_temp = element->FirstChildElement("collide");
				if(elem_temp)
				{
					std::string collide;
					elem_temp->QueryStringAttribute("state", &collide);
					if(collide.compare("yes") == 0)
					{
						m_collide = true;
					}
				}
		}
	}
}

float LogicEntity::getAngle(float x, float y)
{
	if(y == 0 && x == 0)
		return 0.f;
	// plus PI because 0 is up for the engine
	return (atan2f(x, y) + PI) ;
}

void LogicEntity::setSize(const Point2d<float>& size)
{
	m_size = size;
	m_updated = true;
}

void LogicEntity::setRotation(float rotation)
{
	m_rotation = rotation;
	//m_updated = true;
}

void LogicEntity::setPosition(const Point2d<float>& point)
{
	m_position = point;
	m_updated = true;
}

void LogicEntity::setPosition(const Point2d<float>& point, std::string action)
{
	setPosition(point);
	setAction(action);
}

void LogicEntity::setPosition(const Point2d<float>& point, std::string action, float rotation)
{
	setPosition(point);
	setAction(action);
	setRotation(rotation);
}

void LogicEntity::setMove(const Point2d<float>& move)
{
	m_position = m_position + move;
	m_updated = true;
}

void LogicEntity::setMove(const Point2d<float>& move, std::string action)
{
	setMove(move);
	setAction(action);
}

void LogicEntity::setMove(const Point2d<float>& move, std::string action, float rotation)
{
	setMove(move);
	setAction(action);
	setRotation(rotation);
}

void LogicEntity::setAction(std::string action)
{
	m_action = action;
	m_updated = true;
}

void LogicEntity::setUpdated()
{
	m_updated = false;
}

const Point2d<float>& LogicEntity::getPosition()
{
	return m_position;
}

const Point2d<float>& LogicEntity::getSize()
{
	return m_size;
}

float LogicEntity::getRotation()
{
	return m_rotation;
}