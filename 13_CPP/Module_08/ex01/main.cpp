#include "Span.hpp"

int	main( void )
{
	std::cout << BY "Subject Test" RST << std::endl;
	{
		try
		{
			Span sp = Span(5);
			
			sp.addNumber(6);
			sp.addNumber(3);
			sp.addNumber(17);
			sp.addNumber(9);
			sp.addNumber(11);

			std::cout << sp.shortestSpan() << std::endl;
			std::cout << sp.longestSpan() << std::endl;
		}
		catch(const std::exception& e)
		{
			std::cerr << e.what() << std::endl;
		}
	}

	std::cout << BY "\nMy Test 1" RST << std::endl;
	{
		try
		{
			Span sp = Span(8);
			
			sp.addNumber(3);
			sp.addNumber(1);
			sp.addNumber(-4);
			sp.addNumber(1);
			sp.addNumber(5);
			sp.addNumber(9);
			sp.addNumber(-9);
			sp.addNumber(12);
			// sp.addNumber(12);
			
			std::cout << sp.shortestSpan() << std::endl;
			std::cout << sp.longestSpan() << std::endl;
		}
		catch(const std::exception& e)
		{
			std::cerr << e.what() << std::endl;
		}
	}

	std::cout << BY "\nMy Test 2" RST << std::endl;
	{
		try
		{
			Span sp_r = Span(20000);
			sp_r.addNumber(20000, time(NULL));
			std::cout << sp_r.shortestSpan() << std::endl;
			std::cout << sp_r.longestSpan() << std::endl;
		}
		catch(const std::exception& e)
		{
			std::cerr << e.what() << std::endl;
		}
	}

	return 0;
}
