///=============================================================================
///
/// \file           SpriteManager.hpp
/// \class          SpriteManager
///
/// \date           Creation date:  24/02/2009
/// \date           Latest update:  08/08/2009
///
/// \author         Benjamin Rimet, benjamin.rimet@gmail.com
///	\author			Samy Duc, nobunaga.duc@gmail.com
///
/// \brief          Manage sprite with animation, using SFML.
///
///=============================================================================

// Include guard
#ifndef SPRITEMANAGER_HPP_INCLUDED
#define SPRITEMANAGER_HPP_INCLUDED

#include <iostream>
#include <string>
#include <map>
#include <vector>

#include <SFML/Graphics.hpp>
#include "Point2d.hpp"
#include "boost/lexical_cast.hpp"

struct Frame
{
	float frameTime;
	sf::IntRect *Rect;
};

class SpriteManager
{
public:
	SpriteManager(std::string);
	~SpriteManager();

	void setPosition(Point2d<float>);
	void setRotation(float);

	sf::Sprite *getCurrentFrame(std::string action, float frameCall);
	Point2d<float> getCenter();
	Point2d<float> getSize();
	float getRotation();

	bool update();

// Methods
protected:
	bool parserFile(std::string fileName);
	void addFrame(std::string action, struct Frame*);

// Properties
protected:
	std::map<std::string, std::vector<struct Frame*>*> FrameMap;
	// Sprite to be drawn
	sf::Sprite *m_sprite;
	float m_scaling;
	std::string currentAction;
	// Time between last changing frame
	float frameTime;
	// iterator throught FrameVector for animation purpose
	std::vector<struct Frame*>::iterator frame_it;
	// size of the animation
	// getSize attribute on sprite return the size of the spritesheet !
	Point2d<float> m_size;
	bool m_updated;
	
};


#endif

