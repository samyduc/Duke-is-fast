
///=============================================================================
///
/// \file           InputGameState.hpp
/// \class          InputGameState
///
/// \date           Creation date:  03/07/2009
/// \date           Latest update:  08/08/2009
///
/// \author         Benjamin Rimet, benjamin.rimet@gmail.com
///
/// \brief          Behaviour of the Input module when in Game state
///
///=============================================================================

// Include guard
#ifndef INPUTGAMESTATE_HPP_INCLUDED
#define INPUTGAMESTATE_HPP_INCLUDED
//-----------------------------------------------------------------------------/

// Mother classes
#include "InputState.hpp"
//-----------------------------------------------------------------------------/

// Dependancies
#include <map>
#include <string>
//-----------------------------------------------------------------------------/

class InputGameState : public InputState
{
// Methods (InputState)
public:
    bool update();

// Methods
public:
    InputGameState();
    ~InputGameState();

// Methods
protected:

// Properties
protected:

}; // InputGameState

#endif // INPUTGAMESTATE_HPP_INCLUDED


