
///=============================================================================
///
/// \file           CGraphic.hpp
/// \class          CGraphic
///
/// \date           Creation date:  24/02/2009
/// \date           Latest update:  08/08/2009
///
/// \author         Benjamin Rimet, benjamin.rimet@gmail.com
///	\author			Samy Duc, nobunaga.duc@gmail.com
///
/// \brief          An implementation of the Graphic module, using SFML.
///
///=============================================================================

// Include guard
#ifndef CGRAPHIC_HPP_INCLUDED
#define CGRAPHIC_HPP_INCLUDED
//-----------------------------------------------------------------------------/

// Mother classes
#include "IGraphic.hpp"
#include "IModule.hpp"
#include "Singleton.hpp"
//-----------------------------------------------------------------------------/

// Dependancies
#include "GraphicState.hpp"
#include <string>
#include <iostream>
#include "CKernel.hpp"
#include "ILog.hpp"
#include "GraphicGameState.hpp"
#include "SpriteManager.hpp"

#include <boost/lexical_cast.hpp>
#include <SFML/Graphics.hpp>
//-----------------------------------------------------------------------------/

class GraphicState;

class CGraphic : public IGraphic, public IModule, public Singleton<CGraphic>
{
    friend class Singleton<CGraphic>;

// Methods (IModule)
public:
    bool init(const std::string& path);
    bool update();
    void destroy();

    const std::string& name() const;
    void changeState(STATE_ID state);

    void addEntity(int id, const std::string& type);
    void removeEntity(int id);

	void loadMap(const std::string& name);
	// center camera on id
	void setView(int id);

// Methods (IGraphic)
public:
	sf::RenderWindow *getWindow();

	// each label are identified by name
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

	// Interface to python
	void registerCollisionList(int workingID, std::list<GraphicEntity*>*);
	int getWorkingID();
	GraphicEntity* getCollisionList();



// Methods
protected:
	// Fonts
	bool loadFont(std::string);
	sf::Font *getFont(std::string);
	// Images
	bool loadImage(std::string);
	sf::Image *getImage(std::string);
	// Interface to python
	// List of collision
	std::list<GraphicEntity*> *m_registeredCollisionList;
	// current entity treated for collision
	int m_workingID;
// Properties
protected:
    bool m_continue;
	sf::RenderWindow *m_window;
	sf::Color *m_background;
    GraphicState* m_state;

	// Fonts used by every game state (load one time !)
	typedef std::map<std::string, sf::Font*> m_fontMap_t;
	m_fontMap_t m_fontMap;
	// Image used by every game state (load one time !)
	typedef std::map<std::string, sf::Image*> m_imageMap_t;
	m_imageMap_t m_imageMap;
}; // CGraphic

#endif // CGRAPHIC_HPP_INCLUDED


