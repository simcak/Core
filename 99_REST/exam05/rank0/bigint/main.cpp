#include "bigint.hpp"

int main()
{
	const bigint	a(49);
	bigint			b(79), c, d(4294967295), e(d);

	std::cout << "a = " << a << std::endl;
	std::cout << "b = " << b << std::endl;
	std::cout << "c = " << c << std::endl;
	std::cout << "d = " << d << std::endl;
	std::cout << "e = " << e << std::endl;

	std::cout << "\naddition" << std::endl;
	std::cout << "a + b = " << a + b << std::endl;
	std::cout << "(c += a) = " << (c += a) << std::endl;

	std::cout << "b = " << b << std::endl;
	std::cout << "++b = " << ++b << std::endl;
	std::cout << "b++ = " << b++ << std::endl;
	std::cout << "b = " << b << std::endl;

	std::cout << "\ndigit shifting" << std::endl;
	std::cout << "d = " << d << std::endl;
	std::cout << "(b << 20) + 42 = " << ((b << 20) + 42) << std::endl;
	std::cout << "(d >> 2) = " << (d >> 2) << std::endl;
	std::cout << "(d <<= 4) = " << (d <<= 4) << std::endl;
	std::cout << "(d >>= 4) = " << (d >>= 4) << std::endl;
	std::cout << "(d <<= 2) = " << (d <<= (const bigint)2) << std::endl;
	std::cout << "(d >>= 2) = " << (d >>= (const bigint)2) << std::endl;

	std::cout << "\ncomparisons" << std::endl;
	std::cout << "a = " << a << std::endl;
	std::cout << "d = " << d << std::endl;
	std::cout << "e = " << e << std::endl;

	std::cout << "\n(d < a) = " << (d < a) << std::endl;
	std::cout << "(d < e) = " << (d < e) << std::endl;
	std::cout << "(d <= a) = " << (d <= a) << std::endl;
	std::cout << "(d <= e) = " << (d <= e) << std::endl;

	std::cout << "\n(d > a) = " << (d > a) << std::endl;
	std::cout << "(d > e) = " << (d > e) << std::endl;
	std::cout << "(d >= a) = " << (d >= a) << std::endl;
	std::cout << "(d >= e) = " << (d >= e) << std::endl;

	std::cout << "\n(d == a) = " << (d == a) << std::endl;
	std::cout << "(d == e) = " << (d == e) << std::endl;
	std::cout << "(d != a) = " << (d != a) << std::endl;
	std::cout << "(d != e) = " << (d != e) << std::endl;
}
