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