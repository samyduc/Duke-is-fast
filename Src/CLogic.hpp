//=============================================================================
///
/// \file           CLogic.hpp
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

#ifndef CGAMELOGIC_HPP_INCLUDED
#define CGAMELOGIC_HPP_INCLUDED
//-----------------------------------------------------------------------------/

// Mother classes
#include "ILogic.hpp"
#include "IModule.hpp"
#include "Singleton.hpp"
//-----------------------------------------------------------------------------/

// Dependancies
#include <string>
#include <stack>
#include "LogicState.hpp"
#include "LogicGameState.hpp"
#include <boost/timer.hpp>
//-----------------------------------------------------------------------------/

class CLogic : public ILogic, public IModule, public Singleton<CLogic>
{
    friend class Singleton<CLogic>;

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

// Methods 
public:
	void revertLastMove(int id);
	Point2d<float> *getLastMove(int id);
	int getWorkingID();
	void setWorkingID(int id);
	int getWorkingPlayer();
	void popWorkingPlayer();
	void pushWorkingPlayer(int id);

	void setSize(int id, const Point2d<float>&);
	void setAction(int id, std::string);
	void setPosition(int id, const Point2d<float>&);
	void setPosition(int id, const Point2d<float>&, std::string);
	void setPosition(int id, const Point2d<float>&, std::string, float);
	void setMove(int id, const Point2d<float>&);
	void setMove(int id, const Point2d<float>&, std::string);
	void setMove(int id, const Point2d<float>&, std::string, float);
	const Point2d<float>& getPosition(int id);
	void setRotation(int id, float);

// Methods
protected:
    //virtual ~CLogic() {}

// Properties
protected:
	bool m_continue;
	LogicState *m_state;
	boost::timer *m_timer;
	// used to represent the id of the current manipulated object
	int m_workingID;
	// represent the current player
	std::stack<int> m_workingPlayer;
}; 

#endif // 
