///=============================================================================
///
/// \file           CollisionBox.cpp
/// \class          CollisionBox
///
/// \date           Creation date:  24/02/2009
/// \date           Latest update:  08/08/2009
///
///	\author			Samy Duc, nobunaga.duc@gmail.com
///	\author			Valentin Radlo
///
/// \brief          Handle collusion on simple box.
///
///=============================================================================

// Include guard
#ifndef COLLISIONBOX_HPP_INCLUDED
#define COLLISIONBOX_HPP_INCLUDED

#include "Point2d.hpp"
#include <cmath>

class QuadTree;

// The CollisionBox class is entirely based on Valentin Radlo works
// He provided good mathematical demonstration
// and c++ implementation of his algorithm
class CollisionBox
{
// Methods
public :
	CollisionBox(int id, Point2d<float> position, Point2d<float> size, float rotation);
	CollisionBox(Point2d<float> position, Point2d<float> size, float rotation);
	~CollisionBox();

	void setRotation(float rotation);
	void setMove(const Point2d<float>& move);
	void setMove(const Point2d<float>& move, float rotation);
	void setPosition(const Point2d<float>& position);
	void setPosition(const Point2d<float>& position, float rotation);
	Point2d<float> getSize();
	void setSize(const Point2d<float>& size);
	Point2d<float> getPositionOutLine();
	Point2d<float> getSizeOutLine();
	Point2d<float> getPosition();
	float getRotation();
	int getID();


	void RotateAround(CollisionBox*);
	// oriented
	bool checkCollision(CollisionBox*, CollisionBox*);
	// no oriented
	bool checkSimpleCollision(CollisionBox*, CollisionBox*);

// properties
	QuadTree *m_quadTree;

protected:
	int m_id;
	Point2d<float> m_position;
	Point2d<float> m_size;
	float m_rotation;

	Point2d<float> m_positionOutLine;
	Point2d<float> m_sizeOutLine;
	CollisionBox *m_outLineRect;

	void UpdateOutLine();
};

#endif