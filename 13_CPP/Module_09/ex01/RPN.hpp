#ifndef RPN_HPP
# define RPN_HPP

#include <iostream>
#include <stack>
#include <exception>

enum ErrorCode
{
	
};

/* ───────────────────────────────── COLORS ───────────────────────────────── */
#define BR		"\033[1;31m"
#define BG		"\033[1;32m"
#define BY		"\033[1;33m"
#define RST		"\033[0m"

#define BRERR	BR "Error: " RST
#define BREXC	BR "Exception: " RST

/* ───────────────────────────────── CLASSES ──────────────────────────────── */
class RPN
{

	private:
		std::stack<std::string>	_container;

	public:
		/* ───────────────────── Orthodox Canonical Form ──────────────────── */
		RPN();
		RPN(const std::string input);
		RPN(const RPN &copy);
		RPN &operator=(const RPN &);
		~RPN();

		/* ──────────────────────────── getters ───────────────────────────── */

		/* ──────────────────────── member function ───────────────────────── */

		/* ─────────────────────────── exception ──────────────────────────── */
		class placeholder : public std::exception {
			public: const char*		what() const throw();
		};
};


#endif