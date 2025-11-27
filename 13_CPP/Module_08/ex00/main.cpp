#include "easyfind.hpp"
#include <string>
#include <sstream>

int main()
{
	std::list<int> container;
	container.push_back(41);
	container.push_back(42);
	container.push_back(43);

	std::list<int>::const_iterator	i = container.end();
	for (size_t match = 40; match < 45; match++)
	{
		try
		{
			i = ::easyfind(container, match);
		}
		catch(const std::exception& e)
		{
			std::cout << e.what() << std::endl;
		}
	}

	return (0);
}
