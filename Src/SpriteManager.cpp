
// Header of the class
#include "SpriteManager.hpp"

// Dependencies
#include "CKernel.hpp"
#include "IGraphic.hpp"
#include "tinyxml.h"

#define SPRITE_PATH "./Res/Sprites/"

SpriteManager::SpriteManager(std::string sprite)
{
	// MUST keep void value to initiate properly it_frame
	currentAction.assign("");
	frameTime = 0.f;

	m_sprite = new sf::Sprite();
	m_sprite->SetBlendMode(sf::Blend::Alpha);

	// do parsing stuff
	if(!parserFile(sprite))
	{
		delete m_sprite;
		m_sprite = NULL;
	}
}

SpriteManager::~SpriteManager()
{
	if(m_sprite)
	{
		delete m_sprite;
	}

	for(std::map<std::string, std::vector<struct Frame*>*>::iterator i = FrameMap.begin(), e = FrameMap.end(); i != e; ++i) 
	{
		for(std::vector<struct Frame*>::reverse_iterator j = i->second->rbegin(), f = i->second->rend(); j != f; j++)
		{
			delete *j;
		}
		delete i->second;
	}
	FrameMap.clear();
}

// do not check if action are legal !
// illegal action cause seg fault
sf::Sprite *SpriteManager::getCurrentFrame(std::string action, float frameCall)
{
	// Continue current movement
	if(action.compare(currentAction) == 0)
	{
		// frameCall represent the time between last call to this function
		frameTime += frameCall;
		if(frameTime >= (*frame_it)->frameTime)
		{
			if(++frame_it == FrameMap[action]->end())
			{
				frame_it = (FrameMap[action]->begin());
			}
			frameTime = 0.f;
		}
	}
	// Initiate new movement
	else
	{
		// Pick first frame
		std::map<std::string, std::vector<struct Frame*>*>::iterator it = FrameMap.find(action);
		if(it == FrameMap.end())
		{
			frame_it = FrameMap["default"]->begin();
			currentAction.assign("default");
		}
		else
		{
			frame_it = FrameMap[action]->begin();
			currentAction.assign(action);
		}
		m_updated = true;
	}
	float x = boost::lexical_cast<float>((*frame_it)->Rect->Width);
	float y = boost::lexical_cast<float>((*frame_it)->Rect->Height);
	m_size.setX(x);
	m_size.setY(y);
	m_sprite->SetSubRect(*(*frame_it)->Rect);
	m_sprite->SetOrigin(0.5f*m_size.X(), 0.5f*m_size.Y());
	m_sprite->SetScale(m_scaling, m_scaling);

	return m_sprite;
}

void SpriteManager::addFrame(std::string action, struct Frame *frame)
{
	std::map<std::string, std::vector<struct Frame*>*>::iterator it = FrameMap.find(action);
	if(it != FrameMap.end())
	{
		it->second->push_back(frame);
	}
	else
	{
		FrameMap[action] = new std::vector<struct Frame*>();
		FrameMap[action]->push_back(frame);
	}
}

bool SpriteManager::parserFile(std::string fileName)
{
	// convert image filename to sprite filename
	TiXmlDocument doc(SPRITE_PATH + fileName);
	bool toReturn = true;
	if(doc.LoadFile())
	{
		TiXmlHandle hdl(&doc);
		TiXmlElement *elem = hdl.FirstChildElement().Element();
		TiXmlElement *elem_temp = elem->FirstChildElement("image");
		if(elem_temp)
		{
			m_sprite->SetImage( *CKernel::graphic()->getImage(elem_temp->Attribute("href")) );
			elem_temp->QueryFloatAttribute("scaling", &m_scaling);
		}
		else
		{
			m_sprite->SetImage( *CKernel::graphic()->getImage("default.png") );
			m_scaling = 1.f;
		}
		elem_temp = hdl.FirstChildElement().FirstChildElement("action").Element();

		while(elem_temp)
		{
			std::string action = elem_temp->Attribute("id");
			TiXmlElement *elem_frame = elem_temp->FirstChildElement("frame");
			
			while(elem_frame)
			{
				struct Frame* new_frame = new Frame();
				int left, top, right, bottom;
				float timer;
				
				elem_frame->QueryIntAttribute("left", &left);
				elem_frame->QueryIntAttribute("top", &top);
				elem_frame->QueryIntAttribute("right", &right);
				elem_frame->QueryIntAttribute("bottom",&bottom);
				elem_frame->QueryFloatAttribute("s_timer", &timer);

				new_frame->frameTime = timer;
				new_frame->Rect = new sf::Rect<int>(left, top, right-left, bottom-top);
				addFrame(action, new_frame);

				elem_frame = elem_frame->NextSiblingElement();
			}
			elem_temp = elem_temp->NextSiblingElement();
		}
	}
	else
	{
		toReturn = false;
	}
	return toReturn;
}

void SpriteManager::setPosition(Point2d<float> center)
{
	// set Center !
	//m_sprite->SetPosition(center.X() - m_sprite->GetSize().x / 2.f, center.Y() - m_sprite->GetSize().y / 2.f);
	m_sprite->SetPosition(center.X(), center.Y());
}

void SpriteManager::setRotation(float rotation)
{
	m_sprite->SetRotation(rotation);
}

Point2d<float> SpriteManager::getCenter()
{
	return Point2d<float>(m_sprite->GetOrigin().x, m_sprite->GetOrigin().y);
	//return Point2d<float>(m_sprite->GetPosition().x, m_sprite->GetPosition().y);
}
Point2d<float> SpriteManager::getSize()
{
	return m_size;
}

float SpriteManager::getRotation()
{
	return m_sprite->GetRotation();
}

bool SpriteManager::update()
{
	bool toReturn = m_updated;
	m_updated = false;
	return toReturn;
}