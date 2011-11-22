
///=============================================================================
///
/// \file           ILogic.hpp
/// \class          ILogic
///
/// \date           Creation date:  28/12/2009
/// \date           Latest update:  28/12/2009
///
/// \author         Benjamin Rimet, benjamin.rimet@gmail.com
/// \author         Samy Duc, nobunaga.duc@gmail.com
///
/// \brief          An interface for the Logic module.
///
///=============================================================================

// Include guard
#ifndef ILOGIC_HPP_INCLUDED
#define ILOGIC_HPP_INCLUDED
//-----------------------------------------------------------------------------/

// Dependancies
#include <iostream>
#include <string>
#include "Point2d.hpp"
//-----------------------------------------------------------------------------/

// Forward declarations
class IModule;
//-----------------------------------------------------------------------------/

class ILogic
{
// Methods
public:
	virtual void revertLastMove(int id) = 0;
	virtual Point2d<float> *getLastMove(int id) = 0;
	virtual int getWorkingID() = 0;
	virtual void setWorkingID(int) = 0;
	virtual int getWorkingPlayer() = 0;
	virtual void popWorkingPlayer() = 0;
	virtual void pushWorkingPlayer(int) = 0;

	virtual void setSize(int id, const Point2d<float>&) = 0;
	virtual void setAction(int id, std::string action) = 0;
	virtual void setPosition(int id, const Point2d<float>&) = 0;
	virtual void setPosition(int id, const Point2d<float>&, std::string) = 0;
	virtual void setPosition(int id, const Point2d<float>&, std::string, float) = 0;
	virtual void setMove(int id, const Point2d<float>&) = 0;
	virtual void setMove(int id, const Point2d<float>&, std::string) = 0;
	virtual void setMove(int id, const Point2d<float>&, std::string, float) = 0;
	virtual const Point2d<float>& getPosition(int id) = 0;
	virtual void setRotation(int id, float) = 0;
};

#endif 


