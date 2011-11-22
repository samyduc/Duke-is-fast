///=============================================================================
///
/// \file           Entity.hpp
/// \class          Entity
///
/// \date           Creation date:  24/02/2009
/// \date           Latest update:  08/08/2009
///
/// \author         Benjamin Rimet, benjamin.rimet@gmail.com
///	\author			Samy Duc, nobunaga.duc@gmail.com
///
/// \brief          Base class for entity.
///
///=============================================================================

// Include guard
#ifndef ENTITY_HPP_INCLUDED
#define ENTITY_HPP_INCLUDED

#include <iostream>

class Entity
{
public:
	Entity(int id, std::string type);
	~Entity();

	virtual bool update() {return true;};

	int getID();
	std::string getType();
	void setAction(std::string action);
	std::string getAction();

// Methods
protected:
	virtual void parseEntity() {};
	std::string getEntityFileName();

// Properties
protected:
	const int m_id;
	std::string m_action;
	std::string m_type;
	
};

#endif