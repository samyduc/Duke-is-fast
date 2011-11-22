///=============================================================================
///
/// \file           LogicState.cpp
///
///
/// \author         Samy Duc, nobunaga.duc@gmail.com
///
/// \brief          Handle internal logic state
///
///=============================================================================

#include "LogicState.hpp"

#define PATH_CONTROLS "./Res/Config/"


LogicState::~LogicState()
{
	for(std::map<int, LogicEntity*>::iterator i = m_entityMap.begin(), e = m_entityMap.end(); i != e; ++i) 
	{
		delete i->second;
	}
	m_entityMap.clear();
}

void LogicState::revertLastMove(int id)
{
	std::map<int, LogicEntity*>::iterator it = m_entityMap.find(id);
	if(it != m_entityMap.end())
	{
		it->second->revertLastMove();
	}
}

Point2d<float> *LogicState::getLastMove(int id)
{
	Point2d<float> *toReturn = NULL;
	std::map<int, LogicEntity*>::iterator it = m_entityMap.find(id);
	if(it != m_entityMap.end())
	{
		toReturn = it->second->getLastMove();
	}
	return toReturn;
}


LogicEntity* LogicState::getEntity(int id)
{
	LogicEntity* toReturn = NULL;
	std::map<int, LogicEntity*>::iterator it = m_entityMap.find(id);
	if(it != m_entityMap.end())
	{
		toReturn = it->second;
	}
	else
	{
		toReturn = NULL;
	}
	return toReturn;
}

void LogicState::setSize(int id, const Point2d<float>& size)
{
	m_entityMap_t::iterator it;
	it = m_entityMap.find(id);
	if(it != m_entityMap.end())
	{
		it->second->setSize(size);
	}
}

void LogicState::setAction(int id, std::string action)
{
	m_entityMap_t::iterator it;
	it = m_entityMap.find(id);
	if(it != m_entityMap.end())
	{
		it->second->setAction(action);
	}
}

void LogicState::setPosition(int id, const Point2d<float>& position)
{
	m_entityMap_t::iterator it;
	it = m_entityMap.find(id);
	if(it != m_entityMap.end())
	{
		it->second->setPosition(position);
	}
}

void LogicState::setPosition(int id, const Point2d<float>& position, std::string action)
{
	m_entityMap_t::iterator it;
	it = m_entityMap.find(id);
	if(it != m_entityMap.end())
	{
		it->second->setPosition(position, action);
	}
}

void LogicState::setPosition(int id, const Point2d<float>& position, std::string action, float rotation)
{
	m_entityMap_t::iterator it;
	it = m_entityMap.find(id);
	if(it != m_entityMap.end())
	{
		it->second->setPosition(position, action, rotation);
	}
}

void LogicState::setMove(int id, const Point2d<float>& move)
{
	m_entityMap_t::iterator it;
	it = m_entityMap.find(id);
	if(it != m_entityMap.end())
	{
		it->second->setMove(move);
	}
}

void LogicState::setMove(int id, const Point2d<float>& move, std::string action)
{
	m_entityMap_t::iterator it;
	it = m_entityMap.find(id);
	if(it != m_entityMap.end())
	{
		it->second->setMove(move, action);
	}
}

void LogicState::setMove(int id, const Point2d<float>& move, std::string action, float rotation)
{
	m_entityMap_t::iterator it;
	it = m_entityMap.find(id);
	if(it != m_entityMap.end())
	{
		it->second->setMove(move, action, rotation);
	}
}

const Point2d<float>& LogicState::getPosition(int id)
{
	m_entityMap_t::iterator it;
	it = m_entityMap.find(id);
	if(it != m_entityMap.end())
	{
		return it->second->getPosition();
	}
	else
	{
		const Point2d<float> temp_position(0.f, 0.f);
		return temp_position;
	}
}
void LogicState::setRotation(int id, float rotation)
{
	m_entityMap_t::iterator it;
	it = m_entityMap.find(id);
	if(it != m_entityMap.end())
	{
		it->second->setRotation(rotation);
	}
}