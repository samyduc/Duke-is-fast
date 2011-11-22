
///=============================================================================
///
/// \file           CGraphic.cpp
///
/// \date           Creation date:  09/08/2008
/// \date           Latest update:  08/08/2009
///
/// \author         Benjamin Rimet, benjamin.rimet@gmail.com
///	\author			Samy Duc, nobunaga.duc@gmail.com
///
/// \brief          An implementation of the Graphic module, using SFML.
///
///=============================================================================

// Header of the class
#include "CGraphic.hpp"
//-----------------------------------------------------------------------------/

// Define
#define FONT_PATH "./Res/Fonts/"
#define IMAGE_PATH "./Res/Images/"
//-----------------------------------------------------------------------------/

//-----------------------------------------------------------------------------/

bool CGraphic::init(const std::string& path)
{
	m_window = new sf::RenderWindow(sf::VideoMode(800, 600, 32), "Duke");
	m_window->SetFramerateLimit(0);

	m_state = new GraphicState();
	m_continue = true;

	m_background = new sf::Color(0, 0, 0);

	// load default materials
	loadFont("DejaVuSans.ttf");

	CKernel::log()->addLog(this, "CGraphic::init done");
	return(true);
}

bool CGraphic::update()
{
	if(!m_window->IsOpened())
    {
        m_continue = false;
    }
	
	m_window->Clear(*m_background);

	m_continue &= m_state->update();
	m_state->draw();

	m_window->Display();

    return (m_continue);
}

void CGraphic::destroy()
{
	if(m_window->IsOpened())
	{
		m_window->Close();
	}
}

const std::string& CGraphic::name() const
{
    static std::string str("graphic");
    return (str);
}

void CGraphic::addEntity(int id, const std::string& type)
{
	CKernel::log()->addLog(this, "CGraphic::addEntity : " + boost::lexical_cast<std::string>(id) + " " + type);
    m_state->addEntity(id, type);
}

void CGraphic::removeEntity(int id)
{
	CKernel::log()->addLog(this, "CGraphic::removeEntity : " + boost::lexical_cast<std::string>(id));
    m_state->removeEntity(id);
}

void CGraphic::changeState(STATE_ID state)
{
    delete (m_state);
    switch (state)
    {
        case MENU:
            //m_state = new GraphicMenuState(m_mgr);
            break;
        case GAME:
            m_state = new GraphicGameState();
            break;
        default:
            m_state = new GraphicState();
            break;
    }
}

//-----------------------------------------------------------------------------/
// Get
//-----------------------------------------------------------------------------/
sf::RenderWindow *CGraphic::getWindow()
{
	return m_window;
}

// get Font
// if not available try to reload this font
// if not possible try to give the default font
sf::Font *CGraphic::getFont(std::string font)
{
	m_fontMap_t::iterator it;
	sf::Font *toReturn;

	it = m_fontMap.find(font);
	if(it != m_fontMap.end())
	{
		toReturn = it->second;
	}
	else
	{
		if(!loadFont(font))
		{
			CKernel::log()->addLog(this, "CGraphic::getFont cannot get font : " + font);
			//toReturn = new sf::Font();
			//sf::Font::GetDefaultFont()
			toReturn = NULL;
		}
		else
		{
			toReturn = m_fontMap[font];
		}
	}
	return toReturn;
}

sf::Text* CGraphic::getLabel(std::string string_id)
{
	sf::Text* toReturn;
	toReturn = m_state->getLabel(string_id);

	if(!toReturn)
	{
		CKernel::log()->addLog(this, "CGraphic::getLabel label is NULL : " + string_id);
	}
	return toReturn;
}

// Same as getFont
// Nevertheless can return NULL if default.png do not exist
sf::Image *CGraphic::getImage(std::string image)
{
	m_imageMap_t::iterator it;
	sf::Image *toReturn = NULL;

	it = m_imageMap.find(image);
	if(it != m_imageMap.end())
	{
		toReturn = it->second;
	}
	else
	{
		if(!loadImage(image))
		{
			CKernel::log()->addLog(this, "CGraphic::getImage cannot get image : " + image);
			it = m_imageMap.find("default.png");
			if(it != m_imageMap.end())
			{
				toReturn = it->second;
			}
		}
		else
		{
			toReturn = m_imageMap[image];
		}
	}
	return toReturn;	
}

//-----------------------------------------------------------------------------/
// Methods
//-----------------------------------------------------------------------------/
// Load a Font without checking if already allocated
bool CGraphic::loadFont(std::string font)
{
	sf::Font *MyFont;
	MyFont = new sf::Font();
	bool toReturn = true;

	if (!MyFont->LoadFromFile(FONT_PATH + font))
	{
		CKernel::log()->addLog(this, "CGraphic::loadFont unable to load font : " + font);
		toReturn = false;
		delete MyFont;
	}
	else
	{
		m_fontMap[font] = MyFont;
		CKernel::log()->addLog(this, "CGraphic::loadFont font loaded : " + font);
	}
	return toReturn;
}

// Load an Image without checking if already allocated
bool CGraphic::loadImage(std::string image)
{
	sf::Image *MyImage;
	MyImage = new sf::Image();
	bool toReturn = true;

	if (!MyImage->LoadFromFile(IMAGE_PATH + image))
	{
		CKernel::log()->addLog(this, "CGraphic::loadImage unable to load image : " + image);
		toReturn = false;
		delete MyImage;
	}
	else
	{
		m_imageMap[image] = MyImage;
		CKernel::log()->addLog(this, "CGraphic::loadImage image loaded : " + image);
	}
	return toReturn;
}

void CGraphic::addLabel(std::string string_id, sf::Text *label)
{
	m_state->addLabel(string_id, label);
	CKernel::log()->addLog(this, "CGraphic::addLabel label added : " + string_id);
}

void CGraphic::setAction(int id, std::string action)
{
	m_state->setAction(id, action);
}

void CGraphic::setPosition(int id, const Point2d<float>& position)
{
	m_state->setPosition(id, position);
}

void CGraphic::setPosition(int id, const Point2d<float>& position, std::string action)
{
	m_state->setPosition(id, position, action);
}

void CGraphic::setPosition(int id, const Point2d<float>& position, std::string action, float rotation)
{
	m_state->setPosition(id, position, action, rotation);
}

void CGraphic::setMove(int id, const Point2d<float>& position)
{
	m_state->setMove(id, position);
}

void CGraphic::setMove(int id, const Point2d<float>& position, std::string action)
{
	m_state->setMove(id, position, action);
}

void CGraphic::setMove(int id, const Point2d<float>& position, std::string action, float rotation)
{
	m_state->setMove(id, position, action, rotation);
}

const Point2d<float>& CGraphic::getPosition(int id)
{
	return m_state->getPosition(id);
}

void CGraphic::setRotation(int id, float rotation)
{
	m_state->setRotation(id, rotation);
}

void CGraphic::loadMap(const std::string& name)
{
	m_state->loadMap(name);
}

void CGraphic::setView(int id)
{
	m_state->setView(id);
}

// Interface to python
void CGraphic::registerCollisionList(int workingID, std::list<GraphicEntity*>* collisionList)
{
	m_workingID = workingID;
	m_registeredCollisionList = collisionList;
}
int CGraphic::getWorkingID()
{
	return m_workingID;
}

GraphicEntity* CGraphic::getCollisionList()
{
	GraphicEntity *toReturn = NULL;
	if(m_registeredCollisionList->size() > 0)
	{
		toReturn = m_registeredCollisionList->back();
		m_registeredCollisionList->pop_back();
	}
	return toReturn;
}
//