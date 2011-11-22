///=============================================================================
///
/// \file           QuadTree.cpp
///
///
/// \author         Samy Duc, nobunaga.duc@gmail.com
///
/// \brief          Dynamic QuadTree
///
///=============================================================================

#include "QuadTree.hpp"

QuadTree::QuadTree(Point2d<float> position, Point2d<float> size, unsigned int depth, unsigned int maxDepth, unsigned int maxObjects, QuadTree* father)
{
	// set parameters
	m_position = position;
	m_size = size;
	m_depth = ++depth;
	m_maxDepth = maxDepth;
	m_maxObjects = maxObjects;
	m_father = father;
	m_objectBelow = false;

	upperLeft = NULL;
	upperRight = NULL;
	lowerLeft = NULL;
	lowerRight = NULL;

	// recursive call
	// a high value for maxDepth can cause problems
	if(m_depth < m_maxDepth)
	{
		spacePartition();
	}
}

// destructor
// check are performed to provide only one destructor for node and leaf
QuadTree::~QuadTree()
{
	if(upperLeft)
	{
		delete upperLeft;
	}
	if(upperRight)
	{
		delete upperRight;
	}
	if(lowerLeft)
	{
		delete lowerLeft;
	}
	if(lowerRight)
	{
		delete lowerRight;
	}
}

QuadTree* QuadTree::getNextQuad(CollisionBox* object)
{
	Point2d<float> position = object->getPosition();

	QuadTree* toReturn = NULL;
	// left side ?
	if(position.X() <= m_position.X())
	{
		// upper side ?
		if(position.Y() <= m_position.Y())
		{
			toReturn = upperLeft;
		}
		// lower side
		else
		{
			toReturn = lowerLeft;
		}
	}
	// right side
	else
	{
		// upper side ?
		if(position.Y() <= m_position.Y())
		{
			toReturn = upperRight;
		}
		// lower side
		else
		{
			toReturn = lowerRight;
		}
	}
	return toReturn;
}

// check if rectangle can fit in the quadtree
// if not return null to inform the previous quadtree through recursive call
// to place the rectangle in its space
bool QuadTree::quadFit(CollisionBox *object)
{
	bool toReturn = true;
	Point2d<float> position = object->getPosition();
	Point2d<float> centre = position - m_position;
	Point2d<float> size = object->getSize();

	centre.setX(abs(centre.X()));
	centre.setY(abs(centre.Y()));

	if((centre.X() + size.X()/2.f > m_size.X()/2.f) || (centre.Y() + size.Y()/2.f > m_size.Y()/2.f))
	{
		toReturn = false;
	}
	return toReturn;
}

// return true if m_objectBelow must be set to true
// else false
// do not check if quadtree below exist !
bool QuadTree::isObjectBelow()
{
	if(upperLeft->m_objectBelow || upperLeft->m_objectList.empty()
		|| upperRight->m_objectBelow || upperRight->m_objectList.empty()
		|| lowerLeft->m_objectBelow || lowerLeft->m_objectList.empty()
		|| lowerRight->m_objectBelow || lowerRight->m_objectList.empty())
		{
			return true;
		}
		else
		{
			return false;
		}
}


// create 4 new partitions with associated objects
void QuadTree::spacePartition()
{
	// calculate position
	// try to not recalculate already calculate point
	float size_y = m_size.Y() / 4.f;
	float size_x = m_size.X() / 4.f;

	float y_plus = m_position.Y() + size_y;
	float y_minus = m_position.Y() - size_y;
	float x_plus = m_position.X() + size_x;
	float x_minus = m_position.X() - size_x;

	Point2d<float> size = m_size / 2.f;

	// Create 4 new QuadTree
	Point2d<float> upperLeft_position =  Point2d<float>( x_minus, y_minus);
	upperLeft = new QuadTree(upperLeft_position,  size, m_depth, m_maxDepth, m_maxObjects, this);
	
	Point2d<float> upperRight_position =  Point2d<float>( x_plus, y_minus);
	upperRight = new QuadTree(upperRight_position, size, m_depth, m_maxDepth, m_maxObjects, this);

	Point2d<float> lowerleft_position = Point2d<float>( x_minus, y_plus);
	lowerLeft = new QuadTree(lowerleft_position, size, m_depth, m_maxDepth, m_maxObjects, this);

	Point2d<float> lowerRight_position = Point2d<float>( x_plus, y_plus);
	lowerRight = new QuadTree(lowerRight_position, size, m_depth, m_maxDepth, m_maxObjects, this);
}

bool QuadTree::insert(CollisionBox *object)
{
	// if object fit in current quadtree
	if(quadFit(object))
	{
		// get next quadtree
		QuadTree *next = getNextQuad(object);
		// working quadtree to call
		if(next)
		{
			// if insertion done
			if(next->insert(object))
			{
				m_objectBelow = true;
				return true;
			}
			// if insertion cannot be done further
			// must be done here
			else
			{
				m_objectList.push_back(object);
				m_objectBelow = isObjectBelow();
				object->m_quadTree = this;
				return true;
			}
		}
		// if no next
		// store here
		else
		{
			m_objectList.push_back(object);
			object->m_quadTree = this;
			m_objectBelow = false;
			return true;
		}
	}
	// else must be stored in the previous one
	else
	{
		return false;
	}
}

void QuadTree::eraseQuadObject(CollisionBox *object)
{
	for(std::list<CollisionBox *>::iterator it = m_objectList.begin(), e = m_objectList.end(); it != e; ++it)
	{
		if((*it)->getID() == object->getID())
		{
			if(m_depth < m_maxDepth)
			{
				m_objectBelow = isObjectBelow();
			}
			else
			{	
				m_objectBelow = false;
			}
			m_objectList.erase(it);
			break;
		}
	}
}

// erase entity from the tree
// recursive
bool QuadTree::erase(CollisionBox* object)
{
	// if object fit in current quadtree
	if(quadFit(object))
	{
		// get next quadtree
		QuadTree *next = getNextQuad(object);
		// working quadtree to call
		if(next)
		{
			// if insertion done
			if(next->erase(object))
			{
				//m_objectBelow = isObjectBelow();
				return true;
			}
			// if remove cannot be done further
			// must be done here
			else
			{
				eraseQuadObject(object);
				//m_objectBelow = isObjectBelow();
				return true;
			}
		}
		// if no next
		// store here
		else
		{
			eraseQuadObject(object);
			return true;
		}
	}
	// else must be stored in the previous one
	else
	{
		return false;
	}
}

// put in a list every objects which can collide with the pointed object
void QuadTree::getListCollision(CollisionBox* object, std::list<CollisionBox*> *toAppend)
{
	// append object
	toAppend->insert(toAppend->end(), m_objectList.begin(), m_objectList.end());
	// get next quadtree if necessary
	// ie : object in the tree
	//if(m_objectBelow)
	if(m_depth < m_maxDepth)
	{
		if(quadFit(object))
		{
			QuadTree *next = getNextQuad(object);
			if(next)
			{
				// if insertion done
				next->getListCollision(object, toAppend);
			}
		}
		else
		{
			upperLeft->getListCollision(object, toAppend);
			upperRight->getListCollision(object, toAppend);
			lowerLeft->getListCollision(object, toAppend);
			lowerRight->getListCollision(object, toAppend);
		}
	}
}
