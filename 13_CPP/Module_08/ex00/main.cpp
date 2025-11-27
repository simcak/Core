#include "easyfind.hpp"

int main()
{
	std::cout << BY "List-int test" RST << std::endl;

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
	}

	std::cout << BY "\nVector-int test" RST << std::endl;

	{
		std::vector<int> container;
		container.push_back(41);
		container.push_back(42);
		container.push_back(43);
		
		std::vector<int>::const_iterator	i = container.end();
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
	}

	std::cout << BY "\nVector-char test" RST << std::endl;

	{
		std::vector<char> container;
		container.push_back('b');
		container.push_back('c');
		container.push_back('d');
		
		std::vector<char>::const_iterator	i = container.end();
		for (char match = 'a'; match < 'f'; match++)
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
	}

	return (0);
}
