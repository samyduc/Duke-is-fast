
// Header of the class
#include "LogicGameState.hpp"
//-----------------------------------------------------------------------------/

// Dependancies
#include "CKernel.hpp"
#include "IGraphic.hpp"
#include "IInput.hpp"
#include <boost/lexical_cast.hpp>
#include <cmath>
//-----------------------------------------------------------------------------/
#define SPRITE_PATH "./Res/Sprite/"
#define MAP_PATH "./Res/Map/"
//-----------------------------------------------------------------------------/

LogicGameState::LogicGameState() : m_continue(true)
{
	m_sceneNode = new SceneNode();
}

LogicGameState::~LogicGameState()
{
	if(m_sceneNode) delete m_sceneNode;
}

bool LogicGameState::update()
{
	for (std::map<int, LogicEntity*>::iterator it = m_entityMap.begin(), e = m_entityMap.end(); it != e; ++it) 
	{
		it->second->update();
	}
	return m_continue;
}

void LogicGameState::addEntity(int id, const std::string& type)
{
	LogicEntity *toAdd = NULL;
	// check player type
	if(type == "player")
	{
		toAdd = new LogicPlayerEntity(id, type);
	}
	else
	{
		toAdd = new LogicEntity(id, type);
	}
    m_entityMap[id] = toAdd;
	// register to sceneNode if necessary
	if(toAdd->getCollide())
	{
		m_sceneNode->insertEntity(toAdd->getID(), toAdd->getPosition(), toAdd->getSize(), toAdd->getRotation());
	}
}

void LogicGameState::removeEntity(int id)
{
	std::map<int, LogicEntity*>::iterator it = m_entityMap.find(id);
    if (it != m_entityMap.end())
    {
        delete (it->second);
        m_entityMap.erase(it);
    }
}

void LogicGameState::loadMap(std::string name)
{
	// load sceneNode
	// this action will clear the current sceneNode
	m_sceneNode->loadMap(name);
	// add props to sceneNode
	parseProps(name);
}

void LogicGameState::setSize(int id, const Point2d<float>& size)
{
	LogicState::setSize(id, size);
	m_sceneNode->setSizeEntity(id, size);
}

void LogicGameState::parseProps(std::string map_name)
{
	// Parse
	TiXmlDocument doc(std::string(MAP_PATH) + map_name);

	if(doc.LoadFile())
	{
		TiXmlHandle hdl(&doc);
		TiXmlElement *elem = hdl.FirstChildElement("map").Element();

		if(elem)
		{
			// handle entity
			TiXmlElement *elem_temp = elem->FirstChildElement("entity");
			while(elem_temp)
			{
				// iterator
				TiXmlElement *elem_attribute = NULL;
				// default values
				std::string name_entity = "default";
				std::string action = "default";
				Point2d<float> position;
				float angle = 0.f;
				bool complete = true;
				
				// parsing elements
				elem_attribute = elem_temp->FirstChildElement("name");
				if(elem_attribute)
				{
					elem_attribute->QueryStringAttribute("value", &name_entity);
				}
				else complete = false;

				elem_attribute = elem_temp->FirstChildElement("position");
				if(elem_attribute)
				{
					float x = 0.f;
					float y = 0.f;
					float rotation = 0.f;
					elem_attribute->QueryFloatAttribute("x", &x);
					elem_attribute->QueryFloatAttribute("y", &y);
					elem_attribute->QueryFloatAttribute("rotation", &angle);
					position.setX(x);
					position.setY(y);
				}
				else complete = false;

				elem_attribute = elem_temp->FirstChildElement("action");
				if(elem_attribute)
				{
					elem_attribute->QueryStringAttribute("value", &action);
				}
				else complete = false;

				// check xml error happens
				if(complete)
				{
					int id = CKernel::uniqueID();
					CKernel::addEntity(id, name_entity);
					CKernel::graphic()->setPosition(id, position, action, angle);
				}
				elem_temp = elem_temp->NextSiblingElement();
			}

			// props
			elem_temp = elem->FirstChildElement("props");
			while(elem_temp)
			{
				// iterator
				TiXmlElement *elem_attribute = NULL;
				// default values
				bool collide = false;
				std::string sprite = "default.sprite";
				Point2d<float> position;
				float angle = 0.f;
				bool complete = true;

				// parsing elements
				elem_attribute = elem_temp->FirstChildElement("collide");
				if(elem_attribute)
				{
					std::string s_collide;
					elem_attribute->QueryStringAttribute("state", &s_collide);
					if(s_collide == std::string("yes"))
					{
						collide = true;
					}
					else
					{
						collide = false;
					}
				}
				else complete = false;

				elem_attribute = elem_temp->FirstChildElement("sprite");
				if(elem_attribute)
				{
					elem_attribute->QueryStringAttribute("href", &sprite);
				}
				else complete = false;

				elem_attribute = elem_temp->FirstChildElement("position");
				if(elem_attribute)
				{
					float x = 0.f;
					float y = 0.f;
					float rotation = 0.f;
					elem_attribute->QueryFloatAttribute("x", &x);
					elem_attribute->QueryFloatAttribute("y", &y);
					elem_attribute->QueryFloatAttribute("rotation", &angle);
					position.setX(x);
					position.setY(y);
				}
				else complete = false;

				// check xml error happens
				if(complete && collide)
				{
					static int id = 0;
					Point2d<float> size = parseSpriteSize(sprite);
					m_sceneNode->insertProps(--id, position, size, angle);
				}
				elem_temp = elem_temp->NextSiblingElement();
			}
		}
	}
}

// get from the sprite file the size of the sprite in default action
// TO DO : handle different size for collision detection
Point2d<float> LogicGameState::parseSpriteSize(std::string name)
{
	Point2d<float> toReturn;
	// convert image filename to sprite filename
	TiXmlDocument doc(SPRITE_PATH + name);
	if(doc.LoadFile())
	{
		TiXmlHandle hdl(&doc);
		// take the first element
		// certainly the default
		TiXmlElement *elem_temp = hdl.FirstChildElement().FirstChildElement("action").Element();
		// get the size of the default image
		if(elem_temp)
		{
			std::string action = elem_temp->Attribute("id");
			TiXmlElement *elem_frame = elem_temp->FirstChildElement("frame");
			
			if(elem_frame)
			{
				int left, top, right, bottom;
				
				elem_frame->QueryIntAttribute("left", &left);
				elem_frame->QueryIntAttribute("top", &top);
				elem_frame->QueryIntAttribute("right", &right);
				elem_frame->QueryIntAttribute("bottom",&bottom);

				toReturn.setX(boost::lexical_cast<float>(right - left));
				toReturn.setY(boost::lexical_cast<float>(bottom - top));
			}
		}
	}
	return toReturn;
}