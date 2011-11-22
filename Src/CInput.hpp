
///=============================================================================
///
/// \file           CInput.hpp
/// \class          CInput
///
/// \date           Creation date:  24/02/2009
/// \date           Latest update:  08/08/2009
///
/// \author         Benjamin Rimet, benjamin.rimet@gmail.com
///	\author			Samy Duc, nobunaga.duc@gmail.com
///
/// \brief          An implementation of the Input module, using SFML.
///
///=============================================================================

// Include guard
#ifndef CINPUT_HPP_INCLUDED
#define CINPUT_HPP_INCLUDED
//-----------------------------------------------------------------------------/

// Mother classes
#include "IInput.hpp"
#include "IModule.hpp"
#include "Singleton.hpp"
//-----------------------------------------------------------------------------/

// Dependancies
#include "InputState.hpp"
#include <SFML/Window.hpp>
#include <iostream>
#include <map>
#include <boost/python.hpp>
#include <boost/python/detail/wrap_python.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/filesystem.hpp>
#include "ILog.hpp"
#include "CKernel.hpp"

//-----------------------------------------------------------------------------/

class CInput : public IInput, public IModule, public Singleton<CInput>
{
    friend class Singleton<CInput>;

// Methods (IModule)
public:
    bool init(const std::string& path);
    bool update();
    void destroy();

    const std::string& name() const;
    void changeState(STATE_ID state);

    void addEntity(int id, const std::string& type);
    void removeEntity(int id);

	void loadMap(const std::string& name);

// Methods (IInput)
public:

	Point2d<float> *getMousePosition();
	bool isAction(std::string);
	void doAction(std::string);

	bool doEntity(std::string, std::string);

// Methods
protected:
	void registerPython(std::string path, std::map<std::string, bool> &);
	void actionPython(std::string);
	bool doPython(std::string, std::string);

// Properties
protected:
	InputState *m_state;
	std::map<std::string, bool> m_registeredActionMap;
	std::map<std::string, bool> m_registeredEntityMap;
	bool m_continue;

}; // CInput

#endif // CINPUT_HPP_INCLUDED


