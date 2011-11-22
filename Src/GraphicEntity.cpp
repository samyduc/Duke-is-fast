

#include "GraphicEntity.hpp"

GraphicEntity::GraphicEntity(int id, std::string type) : Entity(id, type)
{
	parseEntity();
	// TODO : action must be set by logic game module
	Entity::setAction("default");
	// TODO : position must be set by logic game module
	m_position = m_sprite->getCenter();
	m_updated = false;
}

GraphicEntity::GraphicEntity(int id, std::string type, std::string sprite) : Entity(id, type)
{
	m_sprite = new SpriteManager(sprite);
	// TODO : action must be set by logic game module
	Entity::setAction("default");
	// TODO : position must be set by logic game module
	m_position = m_sprite->getCenter();
	m_updated = false;
}

GraphicEntity::~GraphicEntity()
{
	delete m_sprite;
}

bool GraphicEntity::update()
{
	// set action
	if(m_sprite->update())
	{
		CKernel::logic()->setSize(m_id, m_sprite->getSize());
	}

	return m_updated;
}

void GraphicEntity::setRotation(float rotation)
{
	m_sprite->setRotation(rotation);
	//m_updated = true;
}

void GraphicEntity::setPosition(const Point2d<float>& point)
{
	m_position = point;
	m_sprite->setPosition(m_position);
	m_updated = true;
}

void GraphicEntity::setPosition(const Point2d<float>& point, std::string action)
{
	setPosition(point);
	setAction(action);
}

void GraphicEntity::setPosition(const Point2d<float>& point, std::string action, float rotation)
{
	setPosition(point);
	setAction(action);
	setRotation(rotation);
}

void GraphicEntity::setMove(const Point2d<float>& move)
{
	m_position = m_position + move;
	//m_position = m_sprite->getCenter() + move;
	m_sprite->setPosition(m_position);
	m_updated = true;
}

void GraphicEntity::setMove(const Point2d<float>& move, std::string action)
{
	setMove(move);
	setAction(action);
}

void GraphicEntity::setMove(const Point2d<float>& move, std::string action, float rotation)
{
	setMove(move);
	setAction(action);
	setRotation(rotation);
}

void GraphicEntity::setAction(std::string action)
{
	m_action = action;
	m_updated = true;
}

void GraphicEntity::setUpdated()
{
	m_updated = false;
}

const Point2d<float>& GraphicEntity::getPosition()
{
	return m_position;
}

Point2d<float> GraphicEntity::getSize()
{
	return m_sprite->getSize();
}

float GraphicEntity::getRotation()
{
	return m_sprite->getRotation();
}

/*bool GraphicEntity::checkCollision(GraphicEntity* object)
{
	CollisionBox rectA(getPosition(), getSize(), getRotation());
	CollisionBox rectB(object->getPosition(), object->getSize(), object->getRotation());

	return rectA.checkCollision(&rectA, &rectB);
}*/
//-----------------------------------------------------------------------------/

void GraphicEntity::draw()
{
	sf::RenderWindow *window = CKernel::graphic()->getWindow();

	window->Draw(*m_sprite->getCurrentFrame(Entity::getAction(), window->GetFrameTime()));
}

// Parse entity file to load graphic asset
void GraphicEntity::parseEntity()
{
	TiXmlDocument doc(Entity::getEntityFileName());
	TiXmlElement *elem_temp = NULL;

	if(doc.LoadFile())
	{
		TiXmlHandle hdl(&doc);
		// constant string must be replaced with module name
		TiXmlElement *element = hdl.FirstChildElement().FirstChildElement("graphic").Element();

		if(element)
		{
				elem_temp = element->FirstChildElement("sprite");
				if(elem_temp)
				{
					m_sprite = new SpriteManager(elem_temp->Attribute("href"));
				}
				/*elem_temp = element->FirstChildElement("collide");
				if(elem_temp)
				{
					std::string collide = elem_temp->Attribute("state");
					if(collide.compare("yes") == 0)
					{
						m_collide = true;
					}
					else
					{
						m_collide = false;
					}
				}
				else
				{
					m_collide = false;
				}*/
		}
	}
}