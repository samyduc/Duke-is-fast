//=============================================================================
///
/// \file           CLogic.cpp
/// \class          CLogic
///
/// \date           Creation date:  28/12/2009
/// \date           Latest update:  28/12/2009
///
/// \author         Benjamin Rimet, benjamin.rimet@gmail.com
/// \author         Samy Duc, nobunaga.duc@gmail.com
///
/// \brief          An implementation of the CLogic module.
///
///=============================================================================

// Header of the class
#include "CLogic.hpp"
//-----------------------------------------------------------------------------/

// Dependancies
#include <iostream>
#include <string>
#include "ILogic.hpp"
#include "ILog.hpp"
#include "CKernel.hpp"
//-----------------------------------------------------------------------------/
#define LOGIC_S 0.01666666 //60 Hz
#define LOGIC_CAP 0.5

bool CLogic::init(const std::string& path)
{
	m_state = new LogicState();
	m_timer = new boost::timer();
	
	m_workingID = 0;

	m_continue = true;

	CKernel::log()->addLog(this, "CLogic::init done");
	return m_continue;
}

bool CLogic::update()
{
	static double accumulator = 0;
	
	accumulator += m_timer->elapsed();

	if(accumulator >= LOGIC_CAP)
	{
		accumulator = LOGIC_S;
	}

	if(accumulator >= LOGIC_S)
	{
		m_state->update();
		accumulator -= LOGIC_S;
	}

	m_timer->restart();
    return(m_continue);
}

void CLogic::destroy()
{
	delete m_timer;
	delete m_state;
}

void CLogic::changeState(STATE_ID state)
{
    delete (m_state);
    switch (state)
    {
        case MENU:
            //m_state = new InputMenuState();
            break;
        case GAME:
			// Modify this !
            m_state = new LogicGameState();
            break;
        default:
            m_state = new LogicState();
            break;
    }
}

const std::string& CLogic::name() const
{
    static std::string str("logic");
    return (str);
}

void CLogic::addEntity(int id, const std::string& type)
{
	m_state->addEntity(id, type);
}

void CLogic::removeEntity(int id)
{
	m_state->removeEntity(id);
}

void CLogic::revertLastMove(int id)
{
	m_state->revertLastMove(id);
}

Point2d<float> *CLogic::getLastMove(int id)
{
	return m_state->getLastMove(id);
}

void CLogic::setSize(int id, const Point2d<float>& size)
{
	m_state->setSize(id, size);
}

void CLogic::setAction(int id, std::string action)
{
	m_state->setAction(id, action);
}

void CLogic::setPosition(int id, const Point2d<float>& position)
{
	m_state->setPosition(id, position);
}

void CLogic::setPosition(int id, const Point2d<float>& position, std::string action)
{
	m_state->setPosition(id, position, action);
}

void CLogic::setPosition(int id, const Point2d<float>& position, std::string action, float rotation)
{
	m_state->setPosition(id, position, action, rotation);
}

void CLogic::setMove(int id, const Point2d<float>& position)
{
	m_state->setMove(id, position);
}

void CLogic::setMove(int id, const Point2d<float>& position, std::string action)
{
	m_state->setMove(id, position, action);
}

void CLogic::setMove(int id, const Point2d<float>& position, std::string action, float rotation)
{
	m_state->setMove(id, position, action, rotation);
}

const Point2d<float>& CLogic::getPosition(int id)
{
	return m_state->getPosition(id);
}

void CLogic::setRotation(int id, float rotation)
{
	m_state->setRotation(id, rotation);
}

int CLogic::getWorkingID()
{
	return m_workingID;
}

void CLogic::setWorkingID(int id)
{
	m_workingID = id;
}

int CLogic::getWorkingPlayer()
{
	int workingPlayer = 0;
	if(!m_workingPlayer.empty())
		workingPlayer  = m_workingPlayer.top();
	return workingPlayer;
}

void CLogic::popWorkingPlayer()
{
	if(!m_workingPlayer.empty())
		m_workingPlayer.pop();
}

void CLogic::pushWorkingPlayer(int id)
{
	m_workingPlayer.push(id);
}

void CLogic::loadMap(const std::string& name)
{
	m_state->loadMap(name);
}