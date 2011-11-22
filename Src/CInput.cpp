
///=============================================================================
///
/// \file           CInput.cpp
///
/// \date           Creation date:  24/02/2009
/// \date           Latest update:  08/08/2009
///
/// \author         Benjamin Rimet, benjamin.rimet@gmail.com
/// \author			Samy Duc, nobunaga.duc@gmail.com
///
/// \brief          An implementation of the Input module, using SFML.
///
///=============================================================================

// Header of the class
#include "CInput.hpp"
//-----------------------------------------------------------------------------/

// Dependancies
#include "CKernel.hpp"
#include "IGraphic.hpp"
#include "InputGameState.hpp"

// Wrapper Classes
#include "WKernel.hpp"
#include "WGraphic.hpp"
#include "WInput.hpp"
#include "WUtils.hpp"
#include "WLogic.hpp"

#define ACTION_PATH "./Res/Python/Action/"
#define ENTITY_PATH "./Res/Python/Entity/"
//-----------------------------------------------------------------------------/

//-----------------------------------------------------------------------------/

bool CInput::init(const std::string& path)
{
	sf::RenderWindow *window = CKernel::graphic()->getWindow();
	m_continue = true;

    m_state = new InputState();

	// Initializing python functions and modules
	CKernel::log()->addLog(this, "CInput::init initializing functions and python modules ...");
	Py_Initialize();
	PyImport_AppendInittab("kernel", initkernel);
	PyImport_AppendInittab("wgraphic", initwgraphic);
	PyImport_AppendInittab("winput", initwinput);
	PyImport_AppendInittab("wlogic", initwlogic);
	PyImport_AppendInittab("utils", initutils);
	CKernel::log()->addLog(this, "CInput::init initializing functions and python modules done");

	// Register action
	CKernel::log()->addLog(this, "CInput::init register action ...");
	registerPython(std::string(ACTION_PATH), m_registeredActionMap);
	registerPython(std::string(ENTITY_PATH), m_registeredEntityMap);

	CKernel::log()->addLog(this, "CInput::init done");

    return m_continue;
}

bool CInput::update()
{	
	m_continue &= m_state->update();

    return m_continue;
}

void CInput::destroy()
{
    delete (m_state);
}

const std::string& CInput::name() const
{
    static std::string str("input");
    return (str);
}

void CInput::changeState(STATE_ID state)
{
    delete (m_state);
    switch (state)
    {
        case MENU:
            //m_state = new InputMenuState();
            break;
        case GAME:
			// Modify this !
            m_state = new InputGameState();
            break;
        default:
            m_state = new InputState();
            break;
    }
}

void CInput::loadMap(const std::string& name)
{
}

Point2d<float> *CInput::getMousePosition()
{		
	return m_state->getCursorPosition();
}

void CInput::addEntity(int id, const std::string& type)
{
	if(type.compare("cursor") == 0)
	{
		m_state->setCursor(id);
	}
}

void CInput::removeEntity(int id)
{
}

bool CInput::isAction(std::string action)
{
	return m_state->isAction(action);
}

void CInput::doAction(std::string action)
{
	std::map<std::string, bool>::iterator it;
	it = m_registeredActionMap.find(action);
	if(it != m_registeredActionMap.end())
	{
		// if action registered, must be authorized
		if(it->second)
		{
			actionPython(action);
		}
	}
	else
	{
		m_registeredActionMap[action] = false;
	}
}

// do function specified in entity file
// entity function must return bool
// if a function with implementation return false
// default implementation is added at the end of special implementation
// python script must call special argument !
bool CInput::doEntity(std::string entity, std::string function)
{
	std::map<std::string, bool>::iterator it;
	it = m_registeredEntityMap.find(entity);
	bool toReturn = false;
	if(it != m_registeredEntityMap.end())
	{
		if(it->second)
		{
			toReturn = doPython(entity, function);
		}
	}
	else
	{
		m_registeredEntityMap[entity] = false;
		toReturn = false;
	}
	return toReturn;
}

bool CInput::doPython(std::string entity, std::string s_function)
{
	bool toReturn = false;
	try
	{
		// Retrieve the main module.
		boost::python::object main = boost::python::import("__main__");
	  
		// Retrieve the main module's namespace
		boost::python::object global(main.attr("__dict__"));

		std::string action_path = std::string(ENTITY_PATH) + entity + std::string(".py");
		exec_file(action_path.c_str(), global, global);
		// set function
		boost::python::object o_function = global[s_function];

		toReturn = boost::python::extract<bool>(o_function());

	}
	catch(boost::python::error_already_set const &)
	{
		 PyErr_Print();
	}
	return toReturn;
}

void CInput::actionPython(std::string action)
{
	// Retrieve the main module.
	boost::python::object main = boost::python::import("__main__");
  
	// Retrieve the main module's namespace
	boost::python::object global(main.attr("__dict__"));

	try
	{
		std::string action_path = std::string(ACTION_PATH) + action + std::string(".py");
		exec_file(action_path.c_str(), global, global);
	}
	catch(boost::python::error_already_set const &)
	{
		 PyErr_Print();
	}
}


void CInput::registerPython(std::string path, std::map<std::string, bool> & mapPython)
{
	if(boost::filesystem::is_directory(path))
	{
		for (boost::filesystem::directory_iterator it(path); it !=boost::filesystem::directory_iterator(); ++it)
		{
			if (!boost::filesystem::is_directory(it->status()))
			{
				std::string toMap = it->leaf();
				int index = toMap.rfind(".py");
				toMap.erase(index, 3);
				mapPython[toMap] = true;
			}
		}
		CKernel::log()->addLog(this, std::string("CInput::init path registered") + path);
	}
	else
	{
		CKernel::log()->addLog(this, std::string("CInput::init path registered failed") + path);
	}
}