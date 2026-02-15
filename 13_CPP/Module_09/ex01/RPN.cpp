#include "RPN.hpp"

/* ───────────────────────── Orthodox Canonical Form ──────────────────────── */
RPN::RPN() : _result(0) {}

RPN::RPN(const std::string &input) : _result(0)
{
	std::istringstream	iss(input);
	std::string			tok;

	while (iss >> tok)
		processToken(tok);

	if (_stack.size() != 1)
		throw NotOneOutput();

	_result = _stack.top();
}

RPN::RPN(const RPN &other) : _stack(other._stack), _result(other._result) {}

RPN &RPN::operator=(const RPN &other)
{
	if (this != &other)
	{
		_stack = other._stack;
		_result = other._result;
	}
	return *this;
}

RPN::~RPN() {}

/* ──────────────────────────────── getters ──────────────────────────────── */
long RPN::getResult() const { return _result; }

/* ──────────────────────────── member functions ─────────────────────────── */
void RPN::processToken(const std::string &tok)
{
	if (tok.size() != 1)
		throw tokenLength();

	char tok_c = tok[0];

	if (std::isdigit(tok_c))
		return (_stack.push(static_cast<long>(tok_c - '0')));

	if (tok_c == '+' || tok_c == '-' || tok_c == '*' || tok_c == '/')
		return (applyOperator(tok_c));

	throw invalidChar();
}

void RPN::applyOperator(char op)
{
	if (_stack.size() < 2)
		throw notEnoughNums();

	long b = _stack.top(); _stack.pop();
	long a = _stack.top(); _stack.pop();

	if (op == '+')
		_stack.push(a + b);
	else if (op == '-')
		_stack.push(a - b);
	else if (op == '*')
		_stack.push(a * b);
	else
		(b == 0) ? throw zeroDivision() : _stack.push(a / b);
}

/* ──────────────────────────────── exception ────────────────────────────── */
const char *RPN::invalidChar::what() const throw() {
	return (BRERR "Only numbers, operators, space are accepted.");
}

const char *RPN::tokenLength::what() const throw() {
	return (BRERR "Token must be exactly 1 char: either digit or operator.");
}

const char *RPN::notEnoughNums::what() const throw() {
	return (BRERR "Operator needs 2 RPN expressions.");
}

const char *RPN::zeroDivision::what() const throw() {
	return (BRERR "You tried to devide by zero!");
}

const char *RPN::NotOneOutput::what() const throw() {
	return (BRERR "You have to end with 1! RPN expression.");
}