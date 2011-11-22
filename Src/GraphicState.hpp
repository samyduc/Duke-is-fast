
///=============================================================================
///
/// \file           GraphicState.hpp
/// \class          GraphicState
///
/// \date           Creation date:  13/07/2009
/// \date           Latest update:  08/08/2009
///
/// \author         Benjamin Rimet, benjamin.rimet@gmail.com
///
/// \brief          Base class for all the Graphic module Behaviours.
///
///=============================================================================

// Include guard
#ifndef GRAPHICSTATE_HPP_INCLUDED
#define GRAPHICSTATE_HPP_INCLUDED
//-----------------------------------------------------------------------------/

// Dependancies
#include <string>
#include <map>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Point2d.hpp"
#include "GraphicEntity.hpp"
//-----------------------------------------------------------------------------/

class GraphicState
{
// Methods
public:
	//GraphicState() {}
    ~GraphicState();
    virtual bool update() {return (true);}
	virtual void draw() {}

    virtual void addEntity(int id, const std::string& type) {}
    virtual void removeEntity(int id) {}
	GraphicEntity* getEntity(int id);

	void setView(int id);

	void addLabel(std::string string_id, sf::Text *label);
	sf::Text* getLabel(std::string);
	void setAction(int id, std::string);
	void setPosition(int id, const Point2d<float>&);
	void setPosition(int id, const Point2d<float>&, std::string);
	void setPosition(int id, const Point2d<float>&, std::string, float);
	void setMove(int id, const Point2d<float>&);
	void setMove(int id, const Point2d<float>&, std::string);
	void setMove(int id, const Point2d<float>&, std::string, float);
	const Point2d<float>& getPosition(int id);
	void setRotation(int id, float);

	virtual void loadMap(std::string) {}

// Properties
protected:
	typedef std::map<std::string, sf::Text*> m_labelMap_t;
	m_labelMap_t m_labelMap;
	typedef std::map<int, GraphicEntity*> m_entityMap_t;
	m_entityMap_t m_entityMap;
	sf::View m_view;

// Methods
protected:
	void drawLabel();
	void drawEntity();

	void removeAllEntities();
}; // GraphicState

#endif // GRAPHICSTATE_HPP_INCLUDED


