///=============================================================================
///
/// \file           LogicState.hpp
///
///
/// \author         Samy Duc, nobunaga.duc@gmail.com
///
/// \brief          Handle internal logic state
///
///=============================================================================

// Include guard
#ifndef LOGICSTATE_HPP_INCLUDED
#define LOGICSTATE_HPP_INCLUDED
//-----------------------------------------------------------------------------/

// Dependancies
#include <map>
#include <string>
#include "Point2d.hpp"
#include "LogicEntity.hpp"
//-----------------------------------------------------------------------------/

class LogicState
{
// Methods
public:
	//LogicState();
    ~LogicState();

    virtual bool update() {return (true);}
	virtual void addEntity(int id, const std::string& type) {}
    virtual void removeEntity(int id) {}

	void revertLastMove(int id);
	LogicEntity *getEntity(int id);
	Point2d<float> *getLastMove(int id);
	virtual void loadMap(std::string) {}

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

	// Properties
protected:
	typedef std::map<int, LogicEntity*> m_entityMap_t;
	 m_entityMap_t m_entityMap;

// Methods
protected:


}; 

#endif 


