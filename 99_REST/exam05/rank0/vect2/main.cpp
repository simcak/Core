#include "vect2.hpp"

int main()
{
	vect2		v1;			// 0, 0
	vect2		v2(1, 2);	// 1, 2
	const vect2	v3(v2);		// 1, 2
	vect2		v4 = v2;	// 1, 2

	std::cout << "v1: " << v1 << std::endl;
	std::cout << "v1: " << "{" << v1[0] << ", " << v1[1] << "}" << std::endl;
	std::cout << "v2: " << v2 << std::endl;
	std::cout << "v3: " << v3 << std::endl;
	std::cout << "v4: " << v4 << std::endl;

	std::cout << "\niterators" << std::endl;
	std::cout << v4++ << std::endl; // 2, 3 (but v4 is now 1, 2)
	std::cout << ++v4 << std::endl; // 3, 4
	std::cout << v4-- << std::endl; // 2, 3 (but v4 is now 3, 4)
	std::cout << --v4 << std::endl; // 1, 2

	std::cout << "\nmath operations" << std::endl;
	v2 += v3;			std::cout << "v2 = " << v2 << std::endl;	// 2, 4
	v1 -= v2;			std::cout << "v1 = " << v1 << std::endl;	// -2, -4
	v2 = v3 + v3 * 2;	std::cout << "v2 = " << v2 << std::endl;	// 3, 6
	v2 = 3 * v2;		std::cout << "v2 = " << v2 << std::endl;	// 9, 18
	v2 += v2 += v3;		std::cout << "v2 = " << v2 << std::endl;	// 20, 40
	v1 *= 42;			std::cout << "v1 = " << v1 << std::endl;	// -84, -168
	v1 = v1 - v1 + v1;	std::cout << "v1 = " << v1 << std::endl;	// -84, -168

	std::cout << "\nrest is operation" << std::endl;
	std::cout << "v1: " << v1 << std::endl;
	std::cout << "v2: " << v2 << std::endl;
	std::cout << "-v2: " << -v2 << std::endl;
	std::cout << "v1[1]: " << v1[1] << std::endl;
	v1[1] = 2;
	std::cout << "v1[1]: " << v1[1] << std::endl;
	std::cout << "v3[1]: " << v3[1] << std::endl;
	std::cout << "v1: " << v1 << "\tv3: " << v3 << std::endl;
	std::cout << "v1 == v3: " << (v1 == v3) << std::endl;
	std::cout << "v1 == v1: " << (v1 == v1) << std::endl;
	std::cout << "v1 != v3: " << (v1 != v3) << std::endl;
	std::cout << "v1 != v1: " << (v1 != v1) << std::endl;

	return 0;
}
