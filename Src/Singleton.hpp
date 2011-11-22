
///=============================================================================
///
/// \file           Singleton.hpp
/// \class          Singleton
///
/// \date           Creation date:  18/09/2008
/// \date           Latest update:  08/08/2009
///
/// \author         Benjamin Rimet, benjamin.rimet@gmail.com
/// \author         Samy Duc, nobunaga.duc@gmail.com
///
/// \brief          Allows only one global instance of the class.
///
///=============================================================================

// Include guard
#ifndef SINGLETON_HPP_INCLUDED
#define SINGLETON_HPP_INCLUDED
//-----------------------------------------------------------------------------/

// Mother classes
//#include <boost/noncopyable.hpp>
//-----------------------------------------------------------------------------/

template <typename T>
class Singleton //: private boost::noncopyable
{

public:
    static T* getInstance()
    {
        static T instance;

        return (&instance);
    }
}; // Singleton

#endif // SINGLETON_HPP_INCLUDED


