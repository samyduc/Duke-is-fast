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

#include "CollisionBox.hpp"

// used by CollisionBox
#define DEG_TO_RAD 0.017453f
#define RAD_TO_DEG 57.29577f
//-----------------------------------------------------------------------------/
// Collision
//-----------------------------------------------------------------------------/
CollisionBox::CollisionBox(Point2d<float> position, Point2d<float> size, float rotation) 
{
	m_position= position;
	m_size = size;
	m_rotation = rotation;
	m_outLineRect = NULL;
}

CollisionBox::CollisionBox(int id, Point2d<float> position, Point2d<float> size, float rotation) 
{
	m_id = id;
	m_position= position;
	m_size = size;
	m_rotation = rotation;
	m_outLineRect = NULL;
}

CollisionBox::~CollisionBox()
{
	if(m_outLineRect)
	{
		delete m_outLineRect;
	}
}

void CollisionBox::UpdateOutLine()
{
	float absCosA = abs(cosf(m_rotation * DEG_TO_RAD));
	float absSinA = abs(sinf(m_rotation * DEG_TO_RAD));

	m_sizeOutLine.setX(m_size.X() * absCosA + m_size.Y() * absSinA);
	m_sizeOutLine.setY(m_size.X() * absSinA + m_size.Y() * absCosA);

	m_positionOutLine = m_position;
	if(m_outLineRect)
	{
		delete m_outLineRect;
	}
	m_outLineRect = new CollisionBox(m_positionOutLine, m_sizeOutLine, 0.f);
}

void CollisionBox::RotateAround(CollisionBox* base)
{
	float cosA = cos( -base->m_rotation * DEG_TO_RAD);
	float sinA = sin( -base->m_rotation * DEG_TO_RAD);

	Point2d<float> dposition = m_position - base->m_position;

	Point2d<float> dsecond(dposition.X() * cosA - dposition.Y() * sinA,
						   dposition.X() * sinA + dposition.Y() * cosA);

	m_position = base->m_position + dsecond;
	m_rotation -= base->m_rotation;
	UpdateOutLine();
}

bool CollisionBox::checkSimpleCollision(CollisionBox* rectA, CollisionBox* rectB)
{
	Point2d<float> offsetA = rectA->m_position - rectA->m_size / 2.f;
	Point2d<float> offsetB = rectB->m_position - rectB->m_size / 2.f;
	return !(offsetA.X() > offsetB.X() + rectB->m_size.X()
	|| offsetA.Y() > offsetB.Y() + rectB->m_size.Y()
	|| offsetB.X() > offsetA.X() + rectA->m_size.X()
	|| offsetB.Y() > offsetA.Y() + rectA->m_size.Y());
}

bool CollisionBox::checkCollision(CollisionBox* rect1, CollisionBox* rect2)
{
	bool toReturn = true;

	CollisionBox rectA(*rect1);
	CollisionBox rectB(*rect2);

	rectB.RotateAround(&rectA);

	if(!checkSimpleCollision(&rectA,rectB.m_outLineRect))
	{
		toReturn = false;
		delete rectA.m_outLineRect;
	}
	else
	{
		rectB = *rect2;
		rectA.RotateAround(&rectB);
		if(!checkSimpleCollision(rectA.m_outLineRect,&rectB))
		{
			toReturn = false;
			delete rectB.m_outLineRect;
		}
	}
	return toReturn;
}

void CollisionBox::setRotation(float rotation)
{
	m_rotation = rotation;
}

void CollisionBox::setMove(const Point2d<float>& move)
{
	m_position = m_position + move;
}

void CollisionBox::setMove(const Point2d<float>& move, float rotation)
{
	setMove(move);
	setRotation(rotation);
}

void CollisionBox::setPosition(const Point2d<float>& position)
{
	m_position = position;
}

void CollisionBox::setPosition(const Point2d<float>& position, float rotation)
{
	setPosition(position);
	setRotation(rotation);
}

Point2d<float> CollisionBox::getSize()
{
	return m_size;
}

void CollisionBox::setSize(const Point2d<float>& size)
{
	m_size = size;
}

Point2d<float> CollisionBox::getPosition()
{
	return m_position;
}

float CollisionBox::getRotation()
{
	return m_rotation;
}

int CollisionBox::getID()
{
	return m_id;
}

Point2d<float> CollisionBox::getPositionOutLine()
{
	if(!m_outLineRect)
	{
		UpdateOutLine();
	}
	return m_positionOutLine;
}

Point2d<float> CollisionBox::getSizeOutLine()
{
	if(!m_outLineRect)
	{
		UpdateOutLine();
	}
	return m_sizeOutLine;
}