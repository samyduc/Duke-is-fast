///=============================================================================
///
/// \file           LogicEntity.hpp
///
///
/// \author         Samy Duc, nobunaga.duc@gmail.com
///
/// \brief          Handle internal logic entity state
///
///=============================================================================

// Include guard
#ifndef LOGICENTITY_HPP_INCLUDED
#define LOGICENTITY_HPP_INCLUDED

#include "Entity.hpp"
#include "Point2d.hpp"
#include <string>
#include "tinyxml.h"
#include "IGraphic.hpp"
#include "IInput.hpp"
#include "ILogic.hpp"
#include "IModule.hpp"
#include "CKernel.hpp"
#include <boost/lexical_cast.hpp>

// logic description of entity capabilities
struct logic_descriptor
{
	// hit point
	int hp;
	int armor;
	float velocity;
};

class LogicEntity : public Entity
{
public:
	LogicEntity(int id, std::string type);
	~LogicEntity();

	virtual bool update();

	void revertLastMove();
	Point2d<float> *getLastMove();

	bool getCollide();

	void setSize(const Point2d<float>&);
	void setAction(std::string);
	void setPosition(const Point2d<float>&);
	void setPosition(const Point2d<float>&, std::string);
	void setPosition(const Point2d<float>&, std::string, float);
	void setMove(const Point2d<float>&);
	void setMove(const Point2d<float>&, std::string);
	void setMove(const Point2d<float>&, std::string, float);
	// in degree
	void setRotation(float);
	void setUpdated();

	float getRotation();
	const Point2d<float>& getPosition();
	const Point2d<float>& getSize();

// Methods
protected:
	void parseEntity();
	float getAngle(float x, float y);
// Properties
protected:
	std::string m_action;
	Point2d<float> m_move;
	Point2d<float> m_position;
	Point2d<float> m_size;
	float m_rotation;
	bool m_collide;
	bool m_updated;

	struct logic_descriptor m_descriptor;

};


#endif