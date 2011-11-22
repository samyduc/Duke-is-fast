
///=============================================================================
///
/// \file           CKernel.cpp
///
/// \date           Creation date:  09/08/2008
/// \date           Latest update:  08/08/2009
///
/// \author         Benjamin Rimet, benjamin.rimet@gmail.com
/// \author         Samy Duc, nobunaga.duc@gmail.com
///
/// \brief          Static class that manages all the modules
///
///=============================================================================

// Header of the class
#include "CKernel.hpp"
//-----------------------------------------------------------------------------/

// Dependancies
#include <iostream>
#include <boost/foreach.hpp>
#include <boost/lexical_cast.hpp>
#include "CLog.hpp"
#include "CGraphic.hpp"
#include "CInput.hpp"
#include "CLogic.hpp"

// Debug
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
//-----------------------------------------------------------------------------/

std::vector<IModule*> CKernel::m_moduleVect;
bool CKernel::m_continue = true;

bool CKernel::init(const std::string& path)
{
	
    //CLog must be the first initialized module
    m_moduleVect.push_back(CLog::getInstance());
	m_moduleVect.push_back(CLogic::getInstance());
	m_moduleVect.push_back(CGraphic::getInstance());
	m_moduleVect.push_back(CInput::getInstance());
	

    BOOST_FOREACH(IModule* m, m_moduleVect)
    {
        m_continue &= m->init(path);
    }
	// do more stuff here

	changeState(GAME);
	// return
	return(m_continue);
}

bool CKernel::update()
{
    BOOST_FOREACH(IModule* m, m_moduleVect)
    {
        m_continue &= m->update();
    }
//	Debug Memory leaks
//	_CrtDumpMemoryLeaks();
    return(m_continue);
}

void CKernel::addEntity(int id, const std::string& type)
{
    //std::cout << "adding entity..." << std::endl;
    BOOST_FOREACH(IModule* m, m_moduleVect)
    {
        m->addEntity(id, type);
    }
    //std::cout << "entity added" << std::endl;
}

void CKernel::removeEntity(int id)
{
    //std::cout << "removing entity..." << std::endl;
    BOOST_FOREACH(IModule* m, m_moduleVect)
    {
        m->removeEntity(id);
    }
    //std::cout << "entity removed" << std::endl;
}

void CKernel::changeState(STATE_ID state)
{
    //std::cout << "changing state..." << std::endl;
    BOOST_FOREACH(IModule* m, m_moduleVect)
    {
        m->changeState(state);
    }
    //std::cout << "state changed" << std::endl;
}

void CKernel::loadMap(const std::string &name)
{
	BOOST_FOREACH(IModule* m, m_moduleVect)
    {
        m->loadMap(name);
    }
}

void CKernel::destroy()
{
    BOOST_REVERSE_FOREACH(IModule* m, m_moduleVect)
    {
        m->destroy();
    }
}

int CKernel::uniqueID()
{
    static int id = 0;
    return (++id);
}

ILog* CKernel::log()
{
    return (CLog::getInstance());
}

IGraphic* CKernel::graphic()
{
    return (CGraphic::getInstance());
}

IInput *CKernel::input()
{
	return (CInput::getInstance());
}

ILogic *CKernel::logic()
{
	return (CLogic::getInstance());
}