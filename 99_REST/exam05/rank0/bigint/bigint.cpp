#include "bigint.hpp"

////////////////////////////////////////////////////////////////////////////////
bigint::bigint() : _str("0") {}

bigint::bigint(unsigned int num)
{
	std::stringstream	ss;

	ss << num;
	_str = ss.str();
}

bigint::bigint(const bigint& copy) { *this = copy; }

bigint&	bigint::operator=(const bigint& other)
{
	if(this != &other)
		this->_str = other._str;
	return(*this);
}

bigint::~bigint() {}

////////////////////////////////////////////////////////////////////////////////
static unsigned int	strToUnsignedInt(const std::string &str)
{
	std::stringstream	ss(str);
	unsigned int		output;

	ss >> output;
	return output;
}

static std::string	reverse(const std::string& str)
{
	std::string	revStr;

	for(size_t i = str.length(); i > 0; i--)
		revStr.push_back(str[i - 1]);

	return(revStr);
}

static std::string	addition(const bigint& obj1, const bigint& obj2)
{
	std::string	str1 = reverse(obj1.getStr());
	std::string	str2 = reverse(obj2.getStr());
	size_t		len1 = str1.length(), len2 = str2.length();

	if(len1 > len2)
		for(int diff = len1 - len2; diff > 0; diff--)
			str2.push_back('0');

	else if(len2 > len1)
		for(int diff = len2 - len1; diff > 0; diff--)
			str1.push_back('0');

	unsigned int	carry = 0, digit1, digit2, len = str1.length(), resInt;
	std::string		resStr;

	for(unsigned int i = 0; i < len; i++)
	{
		digit1 = str1[i] - '0';
		digit2 = str2[i] - '0';
		resInt = digit1 + digit2 + carry;
		if(resInt > 9)
		{
			resStr.push_back((resInt % 10) + '0');
			carry = resInt / 10;
		}
		else
		{
			resStr.push_back(resInt + '0');
			carry = 0;
		}
	}
	if(carry != 0)
		resStr.push_back(carry + '0');
	return(reverse(resStr));
}

/////////////////////////////////////////////////////////////////////// addition
bigint	bigint::operator+(const bigint &rhs) const
{
	bigint	output;

	output._str = addition(*this, rhs);
	return output;
}

bigint	&bigint::operator+=(const bigint &rhs)
{
	*this = *this + rhs;
	return *this;
}

bigint	&bigint::operator++()
{
	*this += bigint(1);
	return *this;
}

bigint	bigint::operator++(int)
{
	bigint	output(*this);

	*this += bigint(1);
	return output;
}

/////////////////////////////////// digit shifting by multiplying/dividing by 10
bigint	bigint::operator<<(unsigned int n) const
{
	bigint	output(*this);

	output._str.append(n, '0');
	return output;
}

bigint	bigint::operator>>(unsigned int n) const
{
	bigint			output(*this);
	unsigned int	len = output._str.length();

	len > n ? output._str.erase(len - n) : output._str = "0";
	return output;
}

bigint	&bigint::operator<<=(unsigned int n)
{
	*this = *this << n;
	return(*this);
}

bigint	&bigint::operator>>=(unsigned int n)
{
	*this = *this >> n;
	return(*this);
}

bigint	bigint::operator<<(const bigint &rhs) const
{
	bigint	output;

	output = *this << strToUnsignedInt(rhs.getStr());
	return output;
}

bigint	bigint::operator>>(const bigint &rhs) const
{
	bigint	output;

	output = *this >> strToUnsignedInt(rhs.getStr());
	return output;
}

bigint	&bigint::operator<<=(const bigint &rhs)
{
	*this = *this << rhs;
	return(*this);
}

bigint	&bigint::operator>>=(const bigint &rhs)
{
	*this = *this >> rhs;
	return(*this);
}

/////////////////////////////////////////////////////////// comparison operators
bool	bigint::operator<(const bigint &rhs) const
{ return(strToUnsignedInt(this->getStr()) < strToUnsignedInt(rhs.getStr())); }

bool	bigint::operator<=(const bigint &rhs) const
{ return(strToUnsignedInt(this->getStr()) <= strToUnsignedInt(rhs.getStr())); }

bool	bigint::operator>(const bigint &rhs) const
{ return(strToUnsignedInt(this->getStr()) > strToUnsignedInt(rhs.getStr())); }

bool	bigint::operator>=(const bigint &rhs) const
{ return(strToUnsignedInt(this->getStr()) >= strToUnsignedInt(rhs.getStr())); }

bool	bigint::operator==(const bigint &rhs) const
{ return(strToUnsignedInt(this->getStr()) == strToUnsignedInt(rhs.getStr())); }

bool	bigint::operator!=(const bigint &rhs) const
{ return(!(*this == rhs)); }

////////////////////////////////////////// assignment operator for output stream
std::ostream	&operator<<(std::ostream& os, const bigint& obj)
{
	os << obj.getStr();
	return(os);
}
