
///=============================================================================
///
/// \file           IInput.hpp
/// \class          IInput
///
/// \date           Creation date:  29/12/2008
/// \date           Latest update:  08/08/2009
///
/// \author         Benjamin Rimet, benjamin.rimet@gmail.com
/// \author         Samy Duc, nobunaga.duc@gmail.com
///
/// \brief          An interface for the Input module.
///
///=============================================================================

// Include guard
#ifndef IINPUT_HPP_INCLUDED
#define IINPUT_HPP_INCLUDED
//-----------------------------------------------------------------------------/
#include <SFML/Window.hpp>
#include "Point2d.hpp"
//-----------------------------------------------------------------------------/

class IInput
{
// Methods
public:
	virtual bool isAction(std::string) = 0;
	virtual void doAction(std::string) = 0;
	virtual bool doEntity(std::string, std::string) = 0;
	virtual Point2d<float> *getMousePosition() = 0;
}; // IInput

#endif // IINPUT_HPP_INCLUDED


