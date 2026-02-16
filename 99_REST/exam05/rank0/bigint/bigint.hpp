#ifndef BIGINT_HPP
# define BIGINT_HPP

#include <sstream>
#include <iostream>
#include <string>
#include <cstdlib>

class bigint
{
	private:
		std::string	_str;

	public:
		////////////////////////////////////////////////////////////////////////
		bigint();
		bigint(unsigned int n);
		bigint(bigint const &other);
		bigint &operator=(const bigint &other);
		~bigint();

		////////////////////////////////////////////////////////////////////////
		std::string	getStr() const { return _str; }

		////////////////////////////////////////////////////////////////////////
		bigint	operator+(const bigint &rhs) const;
		bigint	&operator+=(const bigint &rhs);
		bigint	&operator++();
		bigint	operator++(int);

		bigint	operator<<(unsigned int n) const;
		bigint	operator>>(unsigned int n) const;
		bigint	&operator<<=(unsigned int n);
		bigint	&operator>>=(unsigned int n);

		bigint	operator<<(const bigint &rhs) const;
		bigint	operator>>(const bigint &rhs) const;
		bigint	&operator<<=(const bigint &rhs);
		bigint	&operator>>=(const bigint &rhs);

		bool	operator<(const bigint &rhs) const;
		bool	operator<=(const bigint &rhs) const;
		bool	operator>(const bigint &rhs) const;
		bool	operator>=(const bigint &rhs) const;
		bool	operator==(const bigint &rhs) const;
		bool	operator!=(const bigint &rhs) const;
};

////////////////////////////////////////////////////////////////////////////////
std::ostream	&operator<<(std::ostream &os, const bigint &obj);

#endif
