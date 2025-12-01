#include "Span.hpp"

/* ───────────────────────── Orthodox Canonical Form ──────────────────────── */
Span::Span(): _n_stored(0) {}

Span::Span(unsigned int N): _n_stored(N)
{
	this->_num_container.reserve(N);
}

Span::Span(const Span &copy): _n_stored(copy._n_stored)
{
	*this = copy;
}

Span	&Span::operator=(const Span &src)
{
	(void)src;
	return (*this);
}

Span::~Span() {}

/* ───────────────────────────────── getters ──────────────────────────────── */
inline unsigned int	Span::getNStored() const { return this->_n_stored; }

/* ──────────────────────────── member functions ──────────────────────────── */
void	Span::addNumber(int num)
{
	if (this->_num_container.size() >= this->getNStored())
		throw AlreadyFilledException();
	this->_num_container.push_back(num);
}

void	Span::addNumber(unsigned int range, time_t seed)
{
	srand(seed);
	for (size_t i = 0; i < range; i++)
	{
		try
		{
			addNumber(rand());
		}
		catch(const std::exception& e)
		{
			std::cerr << e.what() << '\n';
		}
	}
}

unsigned int Span::shortestSpan() const {
	if (_num_container.size() < 2)
		throw NoSpanFoundException();

	std::vector<int>	c = this->_num_container;
	unsigned int		shortest;

	std::sort(c.begin(), c.end());

	shortest = c.back();
	for (size_t i = 1; i < c.size(); ++i)
		shortest = std::min<unsigned int>(shortest, c[i] - c[i-1]);
	return shortest;
}

unsigned int	Span::longestSpan() const
{
	if (_num_container.size() < 2)
		throw NoSpanFoundException();

	std::vector<int> c = this->_num_container;
	std::vector<int>::iterator min_value;
	std::vector<int>::iterator max_value;

	min_value = std::min_element(c.begin(), c.end());
	max_value = std::max_element(c.begin(), c.end());

	return (*max_value - *min_value);
}

/* ──────────────────────────────── exception ─────────────────────────────── */
const char* Span::AlreadyFilledException::what() const throw()
{
	return (BREXC "There are already N elements stored.");
}

const char* Span::NoSpanFoundException::what() const throw()
{
	return (BREXC "There are no numbers stored, or only one.");
}
