#include "easyfind.hpp"

template <typename C, typename I>
static void	_tester(C& container, I& i, int match_start, int match_end)
{
	for (int match = match_start; match <= match_end; match++)
	{
		try
		{
			i = ::easyfind(container, match);
			std::cout << match << BG " found" RST << std::endl;
		}
		catch(const std::exception& e)
		{
			std::cout << e.what() << std::endl;
		}
	}
}

int main()
{
	std::cout << BY "List-int test" RST << std::endl;

	{
		std::list<int> container;
		container.push_back(41);
		container.push_back(42);
		container.push_back(43);
		
		std::list<int>::const_iterator	i = container.end();
		_tester(container, i, 40, 44);
	}

	std::cout << BY "\nVector-int test" RST << std::endl;

	{
		std::vector<int> container;
		container.push_back(41);
		container.push_back(42);
		container.push_back(43);
		
		std::vector<int>::const_iterator	i = container.end();
		_tester(container, i, 40, 44);
	}

	std::cout << BY "\nVector-char test" RST << std::endl;

	{
		std::vector<char> container;
		container.push_back('b');
		container.push_back('c');
		container.push_back('d');
		
		std::vector<char>::const_iterator	i = container.end();
		_tester(container, i, 'a', 'e');
	}

	return (0);
}
