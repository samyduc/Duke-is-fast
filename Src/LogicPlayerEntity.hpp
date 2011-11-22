// Include guard
#ifndef LOGICPLAYERENTITY_HPP_INCLUDED
#define LOGICPLAYERENTITY_HPP_INCLUDED

#include "LogicEntity.hpp"
#include "Point2d.hpp"
#include <string>
#include <cmath>

class LogicPlayerEntity : public LogicEntity
{
public:
	LogicPlayerEntity(int id, std::string type);
	~LogicPlayerEntity();

	bool update();

// Methods
protected:
// Properties
protected:
	
	
};


#endif