
///=============================================================================
///
/// \file           GraphicGameState.hpp
/// \class          GraphicGameState
///
/// \date           Creation date:  13/07/2009
/// \date           Latest update:  08/08/2009
///
/// \author         Benjamin Rimet, benjamin.rimet@gmail.com
///
/// \brief          Behaviour of the Graphic module when in Game state
///
///=============================================================================

// Include guard
#ifndef GRAPHICGAMESTATE_HPP_INCLUDED
#define GRAPHICGAMESTATE_HPP_INCLUDED
//-----------------------------------------------------------------------------/

// Mother classes
#include "GraphicState.hpp"
//-----------------------------------------------------------------------------/

// Dependancies
#include <list>
#include <map>
#include "SpriteManager.hpp"
#include <SFML/Graphics.hpp>
#include "CKernel.hpp"
#include "IGraphic.hpp"
#include "IInput.hpp"
#include "ILogic.hpp"
#include <boost/foreach.hpp>
#include <boost/lexical_cast.hpp>
#include <iostream>
#include "SpriteManager.hpp"
#include "tinyxml.h"
#include "Point2d.hpp"
#include <vector>
#include "GraphicEntity.hpp"
//-----------------------------------------------------------------------------/

// Forward declarations

//-----------------------------------------------------------------------------/

class GraphicGameState : public GraphicState
{
// Methods (GraphicState)
public:
    bool update();
	void draw();

	void setView(int id);

    void addEntity(int id, const std::string& type);
    void removeEntity(int id);

	GraphicEntity *addProps(int id, const std::string& type, const std::string& sprite);
    void removeProps(int id);

// Methods
public:
	GraphicGameState();
    ~GraphicGameState();

	void loadMap(std::string);

// Methodes
protected:
	void drawProps();
	void removeAllProps();
// Properties
protected:
    bool m_continue;
	std::vector<GraphicEntity*> m_propsVector;
	// vector to store worldmap static components
	// other are treated like entities

	
}; // GraphicGameState

#endif // GRAPHICGAMESTATE_HPP_INCLUDED


