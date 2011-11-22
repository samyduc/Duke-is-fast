//=============================================================================
///
/// \file           CLog.hpp
/// \class          CLog
///
/// \date           Creation date:  28/12/2009
/// \date           Latest update:  28/12/2009
///
/// \author         Benjamin Rimet, benjamin.rimet@gmail.com
/// \author         Samy Duc, nobunaga.duc@gmail.com
///
/// \brief          An implementation of the Log module.
///
///=============================================================================


#ifndef CLOG_HPP_INCLUDED
#define CLOG_HPP_INCLUDED
//-----------------------------------------------------------------------------/

// Mother classes
#include "ILog.hpp"
#include "IModule.hpp"
#include "Singleton.hpp"
//-----------------------------------------------------------------------------/

// Dependancies
#include "boost/date_time/posix_time/posix_time.hpp"
#include <string>
//-----------------------------------------------------------------------------/

class CLog : public ILog, public IModule, public Singleton<CLog>
{
    friend class Singleton<CLog>;

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

// Methods (IDataBase)
public:
    void addLog(IModule *module, std::string log);

// Methods
protected:
    virtual ~CLog() {}


// Properties
protected:
    boost::gregorian::date current_date;
}; //CDataBase

#endif // CLOG_HPP_INCLUDED
