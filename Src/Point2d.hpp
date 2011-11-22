// Include guard
#ifndef POINT2D_HPP_INCLUDED
#define POINT2D_HPP_INCLUDED

#include <iostream>


// Provide common features to handle 2d coordinates
template<typename T>
class Point2d
{
public:
	Point2d();
	Point2d(T x, T y);
	~Point2d();

	void setX(T value) { m_x = value;}
	void setY(T value) { m_y = value;}

	T X() {return m_x;}
	T Y() {return m_y;}

	// Common operators
	Point2d<T> operator+(const Point2d<T> &param);
	Point2d<T> operator-(const Point2d<T> &param);
	Point2d<T> operator/(const Point2d<T> &param);
	Point2d<T> operator/(const T &param);
	Point2d<T> operator*(const Point2d<T> &param);
	Point2d<T> operator=(const Point2d<T> &param);
	bool operator==(const Point2d &param);

private:
	T m_x;
	T m_y;
};

template<typename T>
Point2d<T>::Point2d() : m_x(0), m_y(0)
{
}

template<typename T>
Point2d<T>::Point2d(T x, T y) : m_x(x), m_y(y)
{
}

template<typename T>
Point2d<T>::~Point2d() 
{
}


// Common operators
template<typename T>
Point2d<T> Point2d<T>::operator+(const Point2d<T> &param)
{
	T new_x = m_x + param.m_x;
	T new_y = m_y + param.m_y;
	Point2d<T> toReturn(new_x, new_y);
	return toReturn;
}

template<typename T>
Point2d<T> Point2d<T>::operator-(const Point2d<T> &param)
{
	T new_x = m_x - param.m_x;
	T new_y = m_y - param.m_y;
	Point2d<T> toReturn(new_x, new_y);
	return toReturn;
}

template<typename T>
Point2d<T> Point2d<T>::operator*(const Point2d<T> &param)
{
	T new_x = m_x * param.m_x;
	T new_y = m_y * param.m_y;
	Point2d<T> toReturn(new_x, new_y);
	return toReturn;
}

template<typename T>
Point2d<T> Point2d<T>::operator/(const Point2d<T> &param)
{
	T new_x = m_x / param.m_x;
	T new_y = m_y / param.m_y;
	Point2d<T> toReturn(new_x, new_y);
	return toReturn;
}

template<typename T>
Point2d<T> Point2d<T>::operator/(const T &param)
{
	T new_x = m_x / param;
	T new_y = m_y / param;
	Point2d<T> toReturn(new_x, new_y);
	return toReturn;
}

template<typename T>
Point2d<T> Point2d<T>::operator=(const Point2d<T> &param)
{
	m_x = param.m_x;
	m_y = param.m_y;
	return *this;
}

template<typename T>
bool Point2d<T>::operator==(const Point2d<T> &param)
{
	bool toReturn = false;
	if(m_x == param.m_x && m_y == param.m_y)
	{
		toReturn = true;
	}
	return toReturn;
}

template<typename T>
std::ostream &operator<<(std::ostream &out, Point2d<T> &param)
{
	out << "( " << param.X() << " ; " << param.Y() << " )";
    return out;
}


#endif