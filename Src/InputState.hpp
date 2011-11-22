
///=============================================================================
///
/// \file           InputState.hpp
/// \class          InputState
///
/// \date           Creation date:  03/07/2009
/// \date           Latest update:  08/08/2009
///
/// \author         Benjamin Rimet, benjamin.rimet@gmail.com
///
/// \brief          Base class for all the Input module Behaviours.
///
///=============================================================================

// Include guard
#ifndef INPUTSTATE_HPP_INCLUDED
#define INPUTSTATE_HPP_INCLUDED
//-----------------------------------------------------------------------------/

// Dependancies
#include "IInput.hpp"
#include <boost/bimap.hpp>
#include <map>
#include <string>
#include <SFML/Window.hpp>
#include "tinyxml.h"
#include <SFML/Graphics.hpp>
#include "CKernel.hpp"
#include "IGraphic.hpp"
#include "Point2d.hpp"
#include <boost/lexical_cast.hpp>
//-----------------------------------------------------------------------------/

class InputState
{
// Methods
public:
	InputState();
    ~InputState();

    bool update();
	Point2d<float> *getCursorPosition();
	bool isAction(std::string);
	void setCursor(int id);

// Methods
protected:
	sf::Key::Code getApiKey(std::string);
	sf::Mouse::Button getApiMouse(std::string);

	void parseFile(std::string);
// Properties
protected:
	// warning : sf::Key::Code must be unique !
	typedef boost::bimap<std::string, sf::Key::Code> m_keyMap_t;
	typedef boost::bimap<std::string, sf::Mouse::Button> m_mouseMap_t;
	m_keyMap_t m_keyMap;
	m_mouseMap_t m_mouseMap;
	std::map<std::string, bool> m_actionMap;

	bool m_continue;
	Point2d<float> *cursor_position;
	int cursor_id;
}; // InputState

#endif // INPUTSTATE_HPP_INCLUDED


