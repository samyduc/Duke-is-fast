
///=============================================================================
///
/// \file           GraphicGameState.cpp
///
/// \date           Creation date:  13/07/2009
/// \date           Latest update:  08/08/2009
///
/// \author         Benjamin Rimet, benjamin.rimet@gmail.com
///
/// \brief          Behaviour of the Graphic module when in Game state
///
///=============================================================================

// Header of the class
#include "GraphicGameState.hpp"
//-----------------------------------------------------------------------------/

// Dependancies

//-----------------------------------------------------------------------------/
#define MAP_PATH "./Res/Map/"


GraphicGameState::GraphicGameState() : m_continue(true)
{
	// get default view
	sf::View view = CKernel::graphic()->getWindow()->GetDefaultView();
	// copy
	m_view = view;
}

GraphicGameState::~GraphicGameState()
{
	removeAllProps();
}

void GraphicGameState::removeAllProps()
{
	for(std::vector<GraphicEntity*>::iterator it = m_propsVector.begin(),e = m_propsVector.end(); it != e ; ++it)
	{
		delete *it;
	}
	m_propsVector.clear();
}

bool GraphicGameState::update()
{
	sf::RenderWindow *window = CKernel::graphic()->getWindow();

	float frameRate = 1.f / window->GetFrameTime();

	sf::Text *string_fps = CKernel::graphic()->getLabel("fps");
	string_fps->SetString(boost::lexical_cast<std::string>(frameRate));

	std::list<GraphicEntity*> *collideList = NULL;

	for(m_entityMap_t::iterator it = m_entityMap.begin(), e = m_entityMap.end(); it != e; ++it) 
	{
		// check if size updated
		if(it->second->update())
		{
		}
	}
    return (m_continue);
}

void GraphicGameState::drawProps()
{
	for(std::vector<GraphicEntity*>::iterator it = m_propsVector.begin(),e = m_propsVector.end(); it != e ; ++it)
	{
		(*it)->draw();
	}
}

void GraphicGameState::draw()
{
	// before changing view draw gui
	// TODO : call drawGUI method
	drawProps();
	GraphicState::drawEntity();
	GraphicState::drawLabel();
	// change view
	CKernel::graphic()->getWindow()->SetView(m_view);
}

void GraphicGameState::addEntity(int id, const std::string& type)
{
	GraphicEntity *toAdd = new GraphicEntity(id, type);
    m_entityMap[id] = toAdd;
}

void GraphicGameState::removeEntity(int id)
{
	m_entityMap_t::iterator it = m_entityMap.find(id);
    if (it != m_entityMap.end())
    {
        delete (it->second);
        m_entityMap.erase(it);
    }
}

GraphicEntity *GraphicGameState::addProps(int id, const std::string& type, const std::string& sprite)
{
	GraphicEntity *toAdd = new GraphicEntity(id, type, sprite);
    m_propsVector.push_back(toAdd);
	return toAdd;
}

// consuming !!!
void GraphicGameState::removeProps(int id)
{
	for(std::vector<GraphicEntity*>::iterator it = m_propsVector.begin(),e = m_propsVector.end(); it != e ; ++it)
	{
		if((*it)->getID() == id)
		{
			delete *it;
			m_propsVector.erase(it);
			break;
		}
	}
}

void GraphicGameState::loadMap(std::string map_name)
{
	std::cout << "lolz" << std::endl;
	// clear old map
	removeAllProps();
	GraphicState::removeAllEntities();

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
				if(complete)
				{
					int id = CKernel::uniqueID();
					GraphicEntity *toAdd = addProps(id, "props", sprite);
					toAdd->setPosition(position, std::string("default"), angle);
				}

				elem_temp = elem_temp->NextSiblingElement();
			}
		}
	}
}