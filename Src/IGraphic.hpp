
///=============================================================================
///
/// \file           IGraphic.hpp
/// \class          IGraphic
///
/// \date           Creation date:  11/08/2008
/// \date           Latest update:  08/08/2009
///
/// \author         Benjamin Rimet, benjamin.rimet@gmail.com
/// \author         Samy Duc, nobunaga.duc@gmail.com
///
/// \brief          An interface for the Graphic module.
///
///=============================================================================

// Include guard
#ifndef IGRAPHIC_HPP_INCLUDED
#define IGRAPHIC_HPP_INCLUDED
//-----------------------------------------------------------------------------/

// Dependancies
#include <string>
#include <list>
#include "Point2d.hpp"
#include <SFML/Graphics.hpp>
//-----------------------------------------------------------------------------/

class GraphicEntity;

class IGraphic
{
// Methods
public:
	virtual sf::RenderWindow* getWindow() = 0;
	virtual void addLabel(std::string string_id, sf::Text *label) = 0;
	virtual sf::Text* getLabel(std::string) = 0;
	virtual sf::Font *getFont(std::string font) = 0;
	virtual sf::Image* getImage(std::string) = 0;

	virtual void setView(int id) = 0;

	virtual void setAction(int id, std::string action) = 0;
	virtual void setPosition(int id, const Point2d<float>&) = 0;
	virtual void setPosition(int id, const Point2d<float>&, std::string) = 0;
	virtual void setPosition(int id, const Point2d<float>&, std::string, float) = 0;
	virtual void setMove(int id, const Point2d<float>&) = 0;
	virtual void setMove(int id, const Point2d<float>&, std::string) = 0;
	virtual void setMove(int id, const Point2d<float>&, std::string, float) = 0;
	virtual const Point2d<float>& getPosition(int id) = 0;
	virtual void setRotation(int id, float) = 0;

	// Interface to python
	virtual void registerCollisionList(int workingID, std::list<GraphicEntity*>*) = 0;
	virtual int getWorkingID() = 0;
	virtual GraphicEntity* getCollisionList() = 0;
}; // IGraphic

#endif // IGRAPHIC_HPP_INCLUDED


