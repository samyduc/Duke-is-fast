//=============================================================================
///
/// \file           CLog.cpp
/// \class          CLog
///
/// \date           Creation date:  28/12/2009
/// \date           Latest update:  28/12/2009
///
/// \author         Benjamin Rimet, benjamin.rimet@gmail.com
/// \author         Samy Duc, nobunaga.duc@gmail.com
///
/// \brief          An implementation of the CLog module.
///
///=============================================================================

// Header of the class
#include "CLog.hpp"
//-----------------------------------------------------------------------------/

// Dependancies
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <boost/lexical_cast.hpp>
#include "IModule.hpp"
//-----------------------------------------------------------------------------/

bool CLog::init(const std::string& path)
{
    current_date = boost::gregorian::day_clock::local_day();
    addLog(this, "CLog::init done");

	return(true);
}

bool CLog::update()
{
    if(boost::gregorian::day_clock::local_day() != current_date)
    {
        current_date = boost::gregorian::day_clock::local_day();
        //TODO(#4#) Rotation des logs
    }

    return(true);
}

void CLog::destroy()
{

}

const std::string& CLog::name() const
{
    static std::string str("log");
    return (str);
}

void CLog::changeState(STATE_ID state)
{
	addLog(this, "CLog::changeState changing state to " + boost::lexical_cast<std::string>(static_cast<long>(state)));
}

void CLog::loadMap(const std::string& name)
{
	addLog(this, "CLog::loadMap loading " + name);
}

void CLog::addLog(IModule *module, std::string log)
{
    std::string path = module->name() + ".log";
    std::stringstream toLog;

    boost::posix_time::ptime t(boost::posix_time::second_clock::local_time());
    toLog << t << " " << log << std::endl;
    std::cout << toLog.str();
    std::ofstream log_file(path.c_str(), std::ios::app);

    log_file << toLog.str();
    log_file.close();
}

void CLog::addEntity(int id, const std::string& type)
{
	std::string toLog = "CLog::addEntity : " + boost::lexical_cast<std::string>(id) + " " + type;
	addLog(this, toLog);
}

void CLog::removeEntity(int id)
{
	std::string toLog = "CLog::removeEntity : " + boost::lexical_cast<std::string>(id);
	addLog(this, toLog);
}
