#include "bigint.hpp"

//////////////////////////////////////////////////////////////////////////// OCF
bigint::bigint() : _str("0") {}

bigint::bigint(unsigned int num)
{
	std::stringstream	ss;

	ss << num;
	_str = ss.str();
}

bigint::bigint(const bigint &copy)
{
	if (this != &copy)
		_str = copy._str;
}

bigint	&bigint::operator=(const bigint &other)
{
	if (this != &other)
		_str = other._str;
	return *this;
}

bigint::~bigint() {}

//////////////////////////////////////////////////////////////////////// HELPERS
template <typename I>
static I	strTo(const std::string &str)
{
	std::stringstream	ss(str);
	I					output;

	ss >> output;
	return output;
}

static std::string	reverse(const std::string &str)
{
	std::string	output;

	for (int i = str.size() - 1; i >= 0; --i)
		output.push_back(str[i]);

	return output;
}

static std::string	addition(const bigint &obj1, const bigint &obj2)
{
	std::string	str1 = reverse(obj1.getStr()), str2 = reverse(obj2.getStr());
	int			len1 = str1.size(), len2 = str2.size();

	len1 > len2 ? str2.append(len1 - len2, '0') : str1.append(len2 - len1, '0');

	int			resInt, digit1, digit2, carry = 0;
	std::string	resStr;

	for (size_t i = 0; i < str1.size(); ++i)
	{
		digit1 = str1[i] - '0';
		digit2 = str2[i] - '0';
		resInt = digit1 + digit2 + carry;
		if (resInt > 9)
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
	if (carry != 0)
		resStr.push_back(carry + '0');
	return reverse(resStr);
}

////////////////////////////////////////////////////////////////////// OPERATORS
//--------------------------------------------------------------------- addition
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

//-------------------------------------------------------------------- digishift
bigint	bigint::operator<<(unsigned int n) const
{
	bigint	output(*this);

	output._str.append(n, '0');
	return output;
}

bigint	bigint::operator>>(unsigned int n) const
{
	bigint			output(*this);
	unsigned int	len = output._str.size();

	len > n ? output._str.erase(len - n) : output._str = "0";
	return output;
}

bigint	&bigint::operator<<=(unsigned int n)
{
	*this = *this << n;
	return *this;
}

bigint	&bigint::operator>>=(unsigned int n)
{
	*this = *this >> n;
	return *this;
}

//------------------------------------------------------------------------------
bigint	bigint::operator<<(const bigint &rhs) const
{
	bigint	output;

	output = *this << strTo<unsigned int>(rhs.getStr());
	return output;
}

bigint	bigint::operator>>(const bigint &rhs) const
{
	bigint	output;

	output = *this >> strTo<unsigned int>(rhs.getStr());
	return output;
}

bigint	&bigint::operator<<=(const bigint &rhs)
{
	*this = *this << rhs;
	return *this;
}

bigint	&bigint::operator>>=(const bigint &rhs)
{
	*this = *this >> rhs;
	return *this;
}

//------------------------------------------------------------------ comparation
bool	bigint::operator<(const bigint &rhs) const
{ return strTo<long>(this->getStr()) < strTo<long>(rhs.getStr()); }

bool	bigint::operator<=(const bigint &rhs) const
{ return strTo<long>(this->getStr()) <= strTo<long>(rhs.getStr()); }

bool	bigint::operator>(const bigint &rhs) const
{ return strTo<long>(this->getStr()) > strTo<long>(rhs.getStr()); }

bool	bigint::operator>=(const bigint &rhs) const
{ return strTo<long>(this->getStr()) >= strTo<long>(rhs.getStr()); }

//------------------------------------------------------------------------------
bool	bigint::operator==(const bigint &rhs) const
{ return strTo<long>(this->getStr()) == strTo<long>(rhs.getStr()); }

bool	bigint::operator!=(const bigint &rhs) const
{ return strTo<long>(this->getStr()) != strTo<long>(rhs.getStr()); }


////////////////////////////////////////// assignment operator for output stream
std::ostream	&operator<<(std::ostream &os, const bigint &obj)
{
	os << obj.getStr();
	return os;
}
