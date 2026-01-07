#ifndef RPN_HPP
# define RPN_HPP

#include <iostream>
#include <stack>
#include <exception>
#include <string>
#include <sstream>
#include <cctype>

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
		std::stack<long>	_stack;
		long				_result;

		/* ──────────────────────── member function ───────────────────────── */
		void	processToken(const std::string &tok);
		void	applyOperator(char op);

	public:
		/* ───────────────────── Orthodox Canonical Form ──────────────────── */
		RPN();
		RPN(const std::string &input);
		RPN(const RPN &copy);
		RPN &operator=(const RPN &);
		~RPN();

		/* ──────────────────────────── getters ───────────────────────────── */
		long	getResult() const;

		/* ─────────────────────────── exception ──────────────────────────── */
		class invalidChar : public std::exception {
			public:
				const char *what() const throw();
		};

		class tokenLength : public std::exception {
			public:
				const char *what() const throw();
		};

		class notEnoughNums : public std::exception {
			public:
				const char *what() const throw();
		};

		class zeroDivision : public std::exception {
			public:
				const char *what() const throw();
		};

		class NotOneOutput : public std::exception {
			public:
				const char *what() const throw();
		};
};


#endif