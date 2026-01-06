#include "RPN.hpp"

/* ───────────────────────── Orthodox Canonical Form ──────────────────────── */
RPN::RPN() {}

RPN::RPN(const std::string input) {}

RPN::RPN(const RPN &copy) : _container(copy._container) {}

RPN &RPN::operator=(const RPN &other)
{
	if (this != &other)
		_container = other._container;
	return *this;
}

RPN::~RPN() {}

/* ───────────────────────────────── getters ──────────────────────────────── */

/* ──────────────────────────── member functions ──────────────────────────── */

/* ──────────────────────────────── exception ─────────────────────────────── */
const char *RPN::placeholder::what() const throw() {
	return BREXC "...";
}