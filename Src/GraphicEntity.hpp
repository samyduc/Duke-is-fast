// Include guard
#ifndef GRAPHICENTITY_HPP_INCLUDED
#define GRAPHICENTITY_HPP_INCLUDED

#include "Entity.hpp"
#include "SpriteManager.hpp"
#include "Point2d.hpp"
#include <string>
#include "tinyxml.h"
#include "CollisionBox.hpp"
#include "CKernel.hpp"
#include "IGraphic.hpp"
#include "ILogic.hpp"
#include <boost/lexical_cast.hpp>


class GraphicEntity : public Entity
{
public:
	GraphicEntity(int id, std::string type);
	GraphicEntity(int id, std::string type, std::string sprite);
	~GraphicEntity();

	bool update();
	void draw();

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
	Point2d<float> getSize();

	//bool checkCollision(GraphicEntity*);

// Methods
protected:
	void parseEntity();

// Properties
protected:
	SpriteManager *m_sprite;
	bool m_updated;

	// 2D coordinates of the center
	Point2d<float> m_position;
	
};


#endif