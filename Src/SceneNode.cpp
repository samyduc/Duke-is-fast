///=============================================================================
///
/// \file           SceneNode.cpp
///
///
/// \author         Samy Duc, nobunaga.duc@gmail.com
///
/// \brief          Scene Node
///
///=============================================================================

#include "SceneNode.hpp"

#define CONFIG_PATH "./Res/Config/"
#define MAP_PATH "./Res/Map/"

SceneNode::SceneNode()
{
	// default value
	int m_itemPerCell = 100000;
	int m_maxDepth = 1;
	float m_mapX = 800.f;
	float m_mapY = 600.f;

	parseFile();
}

SceneNode::~SceneNode()
{
	clear();
	if(m_quadTreeEntity)
	{
		delete m_quadTreeEntity;
	}
	if(m_quadTreeProps)
	{
		delete m_quadTreeProps;
	}
}

void SceneNode::insertEntity(int id, const Point2d<float> position, const Point2d<float> size, float rotation)
{
	CollisionBox *toInsert = new CollisionBox(id, position, size, rotation);
	m_entityMap[id] = toInsert;
	m_quadTreeEntity->insert(toInsert);
}

void SceneNode::updateEntity(int id)
{
	m_collisionMap_t::iterator it = m_entityMap.find(id);
	if(it != m_entityMap.end())
	{
		it->second->m_quadTree->eraseQuadObject(it->second);
		m_quadTreeEntity->insert(it->second);
	}
}

void SceneNode::eraseEntity(int id)
{
	m_collisionMap_t::iterator it = m_entityMap.find(id);
	if(it != m_entityMap.end())
	{
		m_quadTreeEntity->erase(it->second);
	}
}

void SceneNode::insertProps(int id, const Point2d<float> position, const Point2d<float> size, float rotation)
{
	CollisionBox *toInsert = new CollisionBox(id, position, size, rotation);
	m_propsMap[id] = toInsert;
	m_quadTreeProps->insert(toInsert);
}

void SceneNode::eraseProps(int id)
{
	m_collisionMap_t::iterator it = m_propsMap.find(id);
	if(it != m_propsMap.end())
	{
		m_quadTreeProps->erase(it->second);
	}
}

// look for entity and his associated quadtree
// remove it
// resize it
// insert it
void SceneNode::setSizeEntity(int id, const Point2d<float>& size)
{
	m_collisionMap_t::iterator it = m_entityMap.find(id);
	if(it != m_entityMap.end())
	{
		it->second->m_quadTree->eraseQuadObject(it->second);
		it->second->setSize(size);
		m_quadTreeEntity->insert(it->second);
	}
}

void SceneNode::clear()
{
	std::vector<CollisionBox*> toDelete;
	// store props
	for(m_collisionMap_t::iterator it = m_propsMap.begin(), e = m_propsMap.end(); it != e; ++it)
	{
		toDelete.push_back(it->second);
	}
	m_propsMap.clear();
	// store entities
	for(m_collisionMap_t::iterator it = m_entityMap.begin(), e = m_entityMap.end(); it != e; ++it)
	{
		toDelete.push_back(it->second);
	}
	m_entityMap.clear();
	// delete everything
	for(std::vector<CollisionBox*>::iterator it = toDelete.begin(), e = toDelete.end(); it != e; ++it)
	{
		delete ((*it));
	}
	toDelete.clear();
}

std::list<CollisionBox*> *SceneNode::update(int)
{
	// clear list collision from previous operation
	m_collisionEntityList.clear();
	m_collisionPropsList.clear();
	m_collisionList.clear();

	// get list
	// TODO : if entity is not present in the scenenode
	// it can be bigger than other cell
	// for this case concatenate list
	/*m_quadTreeEntity->getListCollision(object, &m_collisionEntityList);
	m_quadTreeProps->getListCollision(object, &m_collisionPropsList);

	// props are placed at the beginning
	// only one props is added
	for(std::list<CollisionBox*>::iterator it = m_collisionPropsList.begin(), e = m_collisionPropsList.end(); it != e; it++)
	{
		if(object->checkCollision(*it))
		{
			// DEBUG
			CKernel::graphic()->getLabel("collide")->SetString("true");
			//
			m_collisionList.push_back(*it);
		}
	}

	// iterate through returned list
	for(std::list<CollisionBox*>::iterator it = m_collisionEntityList.begin(), e = m_collisionEntityList.end(); it != e; it++)
	{
		if(object->getID() != (*it)->getID() && object->checkCollision(*it))
		{
			// DEBUG
			CKernel::graphic()->getLabel("collide")->SetString("true");
			//
			m_collisionList.push_back(*it);
		}
	}

	// DEBUG to check collision
	if(m_collisionList.size() == 0)
	{
		CKernel::graphic()->getLabel("collide")->SetString("false");
	}*/
	//
	return &m_collisionList;
}

void SceneNode::loadMap(std::string name)
{
	// clear props and entity map
	clear();

	// parse map file
	TiXmlDocument doc(std::string(MAP_PATH) + name);

	std::cout << std::string(MAP_PATH) + name << std::endl;

	if(doc.LoadFile())
	{
		TiXmlHandle hdl(&doc);
		TiXmlElement *elem = hdl.FirstChildElement().FirstChildElement("size").Element();

		if(elem)
		{
			// get size of the map
			elem->QueryFloatAttribute("x", &m_mapX);
			elem->QueryFloatAttribute("y", &m_mapY);

			if(m_quadTreeEntity) delete m_quadTreeEntity;
			if(m_quadTreeProps) delete m_quadTreeProps;

			m_quadTreeEntity = new QuadTree(Point2d<float>(m_mapX/2.f, m_mapY/2.f), Point2d<float>(m_mapX, m_mapY), 0, m_maxDepth, m_itemPerCell, NULL);	
			m_quadTreeProps = new QuadTree(Point2d<float>(m_mapX/2.f, m_mapY/2.f), Point2d<float>(m_mapX, m_mapY), 0, m_maxDepth, m_itemPerCell, NULL);
		}
	}
}

void SceneNode::parseFile()
{
	TiXmlDocument doc(std::string(CONFIG_PATH) + std::string("SceneNode.cfg"));

	if(doc.LoadFile())
	{
		TiXmlHandle hdl(&doc);
		TiXmlElement *elem = hdl.FirstChildElement().FirstChildElement("quadtree").Element();

		if(elem)
		{
			elem->QueryIntAttribute("item_per_cell", &m_itemPerCell);
			elem->QueryIntAttribute("max_depth", &m_maxDepth);
			// default value
			// avoid null pointer on insert and remove methods
			m_quadTreeEntity = new QuadTree(Point2d<float>(400.f, 300.f), Point2d<float>(800.f, 600.f), 0, m_maxDepth, m_itemPerCell, NULL);	
			m_quadTreeProps = new QuadTree(Point2d<float>(400.f, 300.f), Point2d<float>(800.f, 600.f), 0, m_maxDepth, m_itemPerCell, NULL);
		}
	}
}
