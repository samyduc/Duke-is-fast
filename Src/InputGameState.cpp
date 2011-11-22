
///=============================================================================
///
/// \file           InputGameState.cpp
///
/// \date           Creation date:  03/07/2009
/// \date           Latest update:  08/08/2009
///
/// \author         Benjamin Rimet, benjamin.rimet@gmail.com
///
/// \brief          Behaviour of the Input module when in Game state
///
///=============================================================================

// Header of the class
#include "InputGameState.hpp"
//-----------------------------------------------------------------------------/

// Dependancies
#include "CKernel.hpp"
#include "IGraphic.hpp"
#include "IInput.hpp"
#include <boost/lexical_cast.hpp>
#include <cmath>
//-----------------------------------------------------------------------------/

//-----------------------------------------------------------------------------/

InputGameState::InputGameState()
{
	InputState::parseFile("game");

	sf::Font *MyFont2 = CKernel::graphic()->getFont("DejaVuSans.ttf");
	sf::Text *Text;
	Text = new sf::Text("FPS", *MyFont2);

	Text->SetColor(sf::Color(128, 128, 0));
	Text->Move(100.f, 200.f);
	CKernel::graphic()->addLabel("fps", Text);

	sf::Text *Text2;
	Text2 = new sf::Text("collide", *MyFont2);

	Text2->SetColor(sf::Color(128, 128, 0));
	Text2->Move(400.f, 400.f);
	CKernel::graphic()->addLabel("collide", Text2);

}

InputGameState::~InputGameState()
{

}

bool InputGameState::update()
{
	InputState::update();

	

	return m_continue;
}

