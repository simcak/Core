#ifndef VECT2_HPP
# define VECT2_HPP

#include <iostream>

class vect2
{
	private:
		float	_x;
		float	_y;

	public:
		vect2();
		vect2(float x, float y);
		vect2(const vect2 &copy);
		vect2 &operator=(const vect2 &other);
		~vect2();

		float		&operator[](unsigned int idx);
		const float	&operator[](unsigned int idx) const;

		vect2 &operator++();
		vect2 operator++(int);
		vect2 &operator--();
		vect2 operator--(int);
};

std::ostream &operator<<(std::ostream &os, const vect2 &v);

#endif
