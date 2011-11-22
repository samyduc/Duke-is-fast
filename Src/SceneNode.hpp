// Include guard
#ifndef SCENENODE_HPP_INCLUDED
#define SCENENODE_HPP_INCLUDED

#include "Point2d.hpp"
#include "QuadTree.hpp"
#include "CollisionBox.hpp"
#include "tinyxml.h"
#include <list>
#include <map>
#include <vector>
#include <string>
#include <boost/lexical_cast.hpp>

class SceneNode
{
public:
	SceneNode();
	~SceneNode();

	void insertEntity(int id, const Point2d<float> position, const Point2d<float> size, float rotation);
	void updateEntity(int id);
	void eraseEntity(int id);

	void insertProps(int id, const Point2d<float> position, const Point2d<float> size, float rotation);
	void eraseProps(int id);

	std::list<CollisionBox*> *update(int id);
	void loadMap(std::string name);

	void setSizeEntity(int id, const Point2d<float>& size);

	// drop everything
	void clear();
	
// Methods
protected:
	void parseFile();
// Properties
protected:
	QuadTree *m_quadTreeEntity;
	QuadTree *m_quadTreeProps;
	std::list<CollisionBox*> m_collisionEntityList;
	std::list<CollisionBox*> m_collisionPropsList;
	std::list<CollisionBox*> m_collisionList;

	typedef std::map<int, CollisionBox*> m_collisionMap_t;
	m_collisionMap_t m_propsMap;
	m_collisionMap_t m_entityMap;


	int m_itemPerCell;
	int m_maxDepth;
	float m_mapX;
	float m_mapY;

};

#endif