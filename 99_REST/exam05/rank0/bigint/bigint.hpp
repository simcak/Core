#ifndef BIGINT_HPP
# define BIGINT_HPP

#include <sstream>
#include <iostream>

class bigint
{
	private:
		std::string	_str;

	public:
		//////////////////////////////////////////////////////////////////// OCF
		bigint();
		bigint(unsigned int n);
		bigint(const bigint &copy);
		bigint &operator=(const bigint &other);
		~bigint();

		///////////////////////////////////////////////////////////////// GETTER
		std::string	getStr() const { return _str; }

		////////////////////////////////////////////////////////////// OPERATORS
		//------------------------------------------------------------- addition
		bigint	operator+(const bigint &rhs) const;
		bigint	&operator+=(const bigint &rhs);
		bigint	&operator++();
		bigint	operator++(int);

		//------------------------------------------------------------ digishift
		bigint	operator<<(unsigned int n) const;
		bigint	operator>>(unsigned int n) const;
		bigint	&operator<<=(unsigned int n);
		bigint	&operator>>=(unsigned int n);
		// ---------------------------------------------------------------------
		bigint	operator<<(const bigint &rhs) const;
		bigint	operator>>(const bigint &rhs) const;
		bigint	&operator<<=(const bigint &rhs);
		bigint	&operator>>=(const bigint &rhs);

		// --------------------------------------------------------- comparation
		bool	operator<(const bigint &rhs) const;
		bool	operator<=(const bigint &rhs) const;
		bool	operator>(const bigint &rhs) const;
		bool	operator>=(const bigint &rhs) const;
		// ---------------------------------------------------------------------
		bool	operator==(const bigint &rhs) const;
		bool	operator!=(const bigint &rhs) const;
};

////////////////////////////////////////// assignment operator for output stream
std::ostream	&operator<<(std::ostream &os, const bigint &obj);

#endif
