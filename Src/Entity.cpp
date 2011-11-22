///=============================================================================
///
/// \file           Entity.cpp
/// \class          Entity
///
/// \date           Creation date:  24/02/2009
/// \date           Latest update:  08/08/2009
///
/// \author         Benjamin Rimet, benjamin.rimet@gmail.com
///	\author			Samy Duc, nobunaga.duc@gmail.com
///
/// \brief          Base class for entity.
///
///=============================================================================

#include "Entity.hpp"

#define ENTITY_PATH "./Res/Entity/"

Entity::Entity(int id, std::string type) : m_id(id), m_type(type)
{

}

Entity::~Entity()
{

}

int Entity::getID()
{
	return m_id;
}

std::string Entity::getType()
{
	return m_type;
}

std::string Entity::getAction()
{
	return m_action;
}

void Entity::setAction(std::string action)
{
	m_action = action;
}

std::string Entity::getEntityFileName()
{
	std::string toReturn = ENTITY_PATH;
	toReturn += m_type;
	toReturn += ".entity";
	return toReturn;
}