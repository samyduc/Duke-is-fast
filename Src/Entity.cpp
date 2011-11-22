
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