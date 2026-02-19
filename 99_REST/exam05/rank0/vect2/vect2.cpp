#include "vect2.hpp"

////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////// OCF
vect2::vect2()
{
	_x = 0;
	_y = 0;
}

vect2::vect2(float x, float y)
{
	_x = x;
	_y = y;
}

vect2::vect2(const vect2 &copy)
{
	if (this != &copy)
	{
		_x = copy._x;
		_y = copy._y;
	}
}

vect2 &vect2::operator=(const vect2 &other)
{
	if (this != &other)
	{
		_x = other._x;
		_y = other._y;
	}
	return *this;
}

vect2::~vect2() {}

////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////// square brackets operator []
float	&vect2::operator[](unsigned int idx)
{
	if (idx == 0)
		return _x;
	else if (idx == 1)
		return _y;
	throw std::out_of_range("Index out of bounds");
}

const float	&vect2::operator[](unsigned int idx) const
{
	if (idx == 0)
		return _x;
	else if (idx == 1)
		return _y;
	throw std::out_of_range("Index out of bounds");
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////// iterators
vect2	&vect2::operator++()
{
	++_x; ++_y;
	return *this;
}

vect2	vect2::operator++(int)
{
	vect2	output(*this);

	++_x; ++_y;
	return output;
}

vect2	&vect2::operator--()
{
	--_x; --_y;
	return *this;
}

vect2	vect2::operator--(int)
{
	vect2	output(*this);

	--_x; --_y;
	return output;
}

////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////// math operations
//------------------------------------------------------------------------------
vect2	vect2::operator+(const vect2 &rhs) const
{ return vect2(_x + rhs._x, _y + rhs._y); }

vect2	vect2::operator-(const vect2 &rhs) const
{ return vect2(_x - rhs._x, _y - rhs._y); }

vect2	vect2::operator*(const vect2 &rhs) const
{ return vect2(_x * rhs._x, _y * rhs._y); }

//------------------------------------------------------------------------------
vect2	vect2::operator+(float n) const { return vect2(_x + n, _y + n); }

vect2	vect2::operator-(float n) const { return vect2(_x - n, _y - n); }

vect2	vect2::operator*(float n) const { return vect2(_x * n, _y * n); }

//------------------------------------------------------------------------------
vect2	&vect2::operator+=(const vect2 &rhs)
{
	*this = *this + rhs;
	return *this;
}

vect2	&vect2::operator-=(const vect2 &rhs)
{
	*this = *this - rhs;
	return *this;
}

vect2	&vect2::operator*=(const vect2 &rhs)
{
	*this = *this ;
	return *this;
}

//------------------------------------------------------------------------------
vect2	&vect2::operator+=(float n)
{
	*this = *this + n;
	return *this;
}

vect2	&vect2::operator-=(float n)
{
	*this = *this - n;
	return *this;
}

vect2	&vect2::operator*=(float n)
{
	*this = *this * n;
	return *this;
}

/////////////////////////////////////////////////////////////////////// negation
vect2	vect2::operator-() const
{
	vect2	output = *this * -1;
	return output;
}

////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////// comperation
bool	vect2::operator==(const vect2 &rhs) const
{
	if (_x == rhs._x && _y == rhs._y)
		return true;
	return false;
}

bool	vect2::operator!=(const vect2 &rhs) const
{
	if (_x != rhs._x || _y != rhs._y)
		return true;
	return false;
}

////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////// out of class operators
vect2	operator*(float lhs, const vect2 &rhs)
{
	vect2	output(rhs);

	output *= lhs;
	return output;
}

std::ostream	&operator<<(std::ostream &os, const vect2 &v)
{
	return os << "{" << v[0] << ", " << v[1] << "}";
}
