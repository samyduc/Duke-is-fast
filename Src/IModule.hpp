
///=============================================================================
///
/// \file           IModule.hpp
/// \class          IModule
///
/// \date           Creation date:  31/12/2008
/// \date           Latest update:  08/08/2009
///
/// \author         Benjamin Rimet, benjamin.rimet@gmail.com
/// \author         Samy Duc, nobunaga.duc@gmail.com
///
/// \brief          Interface used by all modules
///
///=============================================================================

// Include guard
#ifndef IMODULE_HPP_INCLUDED
#define IMODULE_HPP_INCLUDED
//-----------------------------------------------------------------------------/

// Dependancies
#include <string>
//-----------------------------------------------------------------------------/

// Enum
enum STATE_ID
    {
        MENU,
        GAME
    };
//-----------------------------------------------------------------------------/

class IModule
{
// Methods
public:
    virtual bool init(const std::string& path) = 0;
    virtual bool update() = 0;
    virtual void destroy() = 0;

    virtual const std::string& name() const = 0;
	virtual void changeState(STATE_ID state) = 0;

    virtual void addEntity(int id, const std::string& type) = 0;
    virtual void removeEntity(int id) = 0;

	virtual void loadMap(const std::string &name) = 0;
}; // IModule

#endif // IMODULE_HPP_INCLUDED


