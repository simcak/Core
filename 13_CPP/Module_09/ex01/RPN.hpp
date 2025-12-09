#ifndef RPN_HPP
# define RPN_HPP

#include <iostream>

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
		/* data */
	public:
		/* ───────────────────── Orthodox Canonical Form ──────────────────── */
		RPN(/* args */);
		~RPN();

		/* ──────────────────────────── getters ───────────────────────────── */

		/* ──────────────────────── member function ───────────────────────── */

		/* ─────────────────────────── exception ──────────────────────────── */

};


#endif