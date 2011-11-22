

// Header of the class
#include "GraphicState.hpp"

#include <map>
#include "CKernel.hpp"
#include "IGraphic.hpp"

GraphicState::~GraphicState()
{
	for(m_labelMap_t::iterator i = m_labelMap.begin(), e = m_labelMap.end(); i != e; ++i) 
	{
		delete i->second;
	}
	m_labelMap.clear();

	for(m_entityMap_t::iterator i = m_entityMap.begin(), e = m_entityMap.end(); i != e; ++i) 
	{
		delete i->second;
	}
	m_entityMap.clear();
}

void GraphicState::drawEntity()
{
	for (m_entityMap_t::iterator it = m_entityMap.begin(), e = m_entityMap.end(); it != e; ++it) 
	{
		it->second->draw();
	}
}

void GraphicState::drawLabel()
{
	sf::RenderWindow *window = CKernel::graphic()->getWindow();

	for (m_labelMap_t::iterator it = m_labelMap.begin(), e = m_labelMap.end(); it != e; ++it) 
	{
		window->Draw(*(it->second));
	}
}

void GraphicState::addLabel(std::string string_id, sf::Text *label)
{
	m_labelMap[string_id] = label;
}

sf::Text* GraphicState::getLabel(std::string label)
{
	sf::Text* toReturn = NULL;
	m_labelMap_t::iterator it = m_labelMap.find(label);
	if(it != m_labelMap.end())
	{
		toReturn = it->second;
	}
	else
	{
		toReturn = NULL;
	}
	return toReturn;
}

void GraphicState::setView(int id)
{
	m_entityMap_t::iterator it = m_entityMap.find(id);
    if (it != m_entityMap.end())
    {
       Point2d<float> pos = it->second->getPosition();
	   m_view.SetCenter(pos.X(), pos.Y());
    }
}

GraphicEntity* GraphicState::getEntity(int id)
{
	GraphicEntity* toReturn = NULL;
	m_entityMap_t::iterator it = m_entityMap.find(id);
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

void GraphicState::removeAllEntities()
{
	// use of a temporary vector to stock id
	// because you cannot iterate through a map and modify it !
	std::vector<int> temp_id;
	for(m_entityMap_t::iterator it = m_entityMap.begin(), e = m_entityMap.end(); it != e; ++it) 
	{
		temp_id.push_back(it->second->getID());
	}

	for(std::vector<int>::iterator it = temp_id.begin(), e = temp_id.end(); it != e; ++it)
	{
		CKernel::removeEntity((*it));
	}
}

void GraphicState::setAction(int id, std::string action)
{
	m_entityMap_t::iterator it;
	it = m_entityMap.find(id);
	if(it != m_entityMap.end())
	{
		it->second->setAction(action);
	}
}

void GraphicState::setPosition(int id, const Point2d<float>& position)
{
	m_entityMap_t::iterator it;
	it = m_entityMap.find(id);
	if(it != m_entityMap.end())
	{
		it->second->setPosition(position);
	}
}

void GraphicState::setPosition(int id, const Point2d<float>& position, std::string action)
{
	m_entityMap_t::iterator it;
	it = m_entityMap.find(id);
	if(it != m_entityMap.end())
	{
		it->second->setPosition(position, action);
	}
}

void GraphicState::setPosition(int id, const Point2d<float>& position, std::string action, float rotation)
{
	m_entityMap_t::iterator it;
	it = m_entityMap.find(id);
	if(it != m_entityMap.end())
	{
		it->second->setPosition(position, action, rotation);
	}
}

void GraphicState::setMove(int id, const Point2d<float>& move)
{
	m_entityMap_t::iterator it;
	it = m_entityMap.find(id);
	if(it != m_entityMap.end())
	{
		it->second->setMove(move);
	}
}

void GraphicState::setMove(int id, const Point2d<float>& move, std::string action)
{
	m_entityMap_t::iterator it;
	it = m_entityMap.find(id);
	if(it != m_entityMap.end())
	{
		it->second->setMove(move, action);
	}
}

void GraphicState::setMove(int id, const Point2d<float>& move, std::string action, float rotation)
{
	m_entityMap_t::iterator it;
	it = m_entityMap.find(id);
	if(it != m_entityMap.end())
	{
		it->second->setMove(move, action, rotation);
	}
}

const Point2d<float>& GraphicState::getPosition(int id)
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
void GraphicState::setRotation(int id, float rotation)
{
	m_entityMap_t::iterator it;
	it = m_entityMap.find(id);
	if(it != m_entityMap.end())
	{
		it->second->setRotation(rotation);
	}
}
