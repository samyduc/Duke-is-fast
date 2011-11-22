
// Include guard
#ifndef LOGICGAMESTATE_HPP_INCLUDED
#define LOGICGAMESTATE_HPP_INCLUDED
//-----------------------------------------------------------------------------/

// Mother classes
#include "LogicState.hpp"
//-----------------------------------------------------------------------------/

// Dependancies
#include <map>
#include <string>
#include "SceneNode.hpp"
#include "LogicEntity.hpp"
#include "LogicPlayerEntity.hpp"
#include <boost/lexical_cast.hpp>
//-----------------------------------------------------------------------------/

class LogicGameState : public LogicState
{

// Methods
public:
    LogicGameState();
    ~LogicGameState();

	void addEntity(int id, const std::string& type);
    void removeEntity(int id);

	bool update();
	void loadMap(std::string name);

	void setSize(int id, const Point2d<float>&);

// Methods
protected:
	void parseProps(std::string name);
	Point2d<float> parseSpriteSize(std::string name);
// Properties
protected:
	bool m_continue;
	SceneNode *m_sceneNode;

}; 

#endif 


