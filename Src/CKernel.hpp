
///=============================================================================
///
/// \file           CKernel.hpp
/// \class          CKernel
///
/// \date           Creation date:  09/08/2008
/// \date           Latest update:  08/08/2009
///
/// \author         Benjamin Rimet, benjamin.rimet@gmail.com
/// \author         Samy Duc, nobunaga.duc@gmail.com
///
/// \brief          Static class that manages all the modules
///
///=============================================================================

// Include guard
#ifndef CKERNEL_HPP_INCLUDED
#define CKERNEL_HPP_INCLUDED
//-----------------------------------------------------------------------------/

// Dependancies
#include <vector>
#include <string>
#include "IModule.hpp"
//-----------------------------/

// Forward declarations
class IModule;
class ILog;
class IGraphic;
class IInput;
class ILogic;
//-----------------------------------------------------------------------------/

class CKernel
{
// Methods
public:
    static bool init(const std::string& path);
    static bool update();
    static void destroy();

    static int CKernel::uniqueID();
	static void CKernel::changeState(STATE_ID state);

    static void addEntity(int id, const std::string& type);
    static void removeEntity(int id);

	static void loadMap(const std::string &name);

    static ILog* log();
	static IGraphic* graphic();
	static IInput* input();
	static ILogic* logic();

protected:
    static std::vector<IModule*> m_moduleVect;
	static bool m_continue;
}; // CKernel-



#endif // CKERNEL_HPP_INCLUDED


