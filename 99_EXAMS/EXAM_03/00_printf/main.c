#include <unistd.h>		// write
#include <stdarg.h>		// va_list, va_start, va_end
#include <stdlib.h>		// EXIT_SUCCESS

#include <stdio.h>		// printf - for testing
#define B	 	"\033[0;34m"
#define R 		"\033[0;31m"
#define RST 	"\033[0m"

/*
	generally we have to remember those three functions:
	- va_start: initializes the va_list variable to the first argument after the string s
	- va_end: cleans up the va_list variable
	- va_arg: returns the next argument in the va_list variable
	libraries:
	- stdarg.h
	- unistd.h
*/

/*
	putstr is a function that takes a string str and prints it to the standard output.
	- we are iterating through the string str and printing each character to the standard output.
	- we are returning the number of characters printed.
*/
int	putstr(char *str)
{
	int i = -1;

	while (str[++i])
		write(1, &str[i], 1);
	return i;
}

/*
	putnum is a recursive function that takes a long number num and an integer base.
	- if the number is negative, we print the '-' character and call putnum recursively
	with the number num * -1 and the base base.
	- if the number divided by the base is 0, we print the character from the string
	"0123456789abcdef" at the index num % base.
	- otherwise, we call putnum recursively with the number num / base and the base base
	and add to it the result of putnum recursively with the number num % base and the base base.

*/
int putnum(long num, int base)
{
	char *b = "0123456789abcdef";

	if (num < 0)
		return write(1, "-", 1) + putnum(num * -1, base);
	if (num / base == 0)
		return write(1, &b[num % base], 1);
	return putnum(num / base, base) + putnum(num % base, base);
}

/*
	ptf is a recursive function that takes the string s, the va_list variable args,
	the index i (index for iterating through the string s), and the number of characters
	printed n (to count how many chars we printed).
	- if the character at index i is the null terminator, we return n.
	- if the character at index i is '%' and the next character is 's', we call ptf
	recursively with the string s, the va_list variable args, the index i + 2 (to skip
	the '%s'), and the number of characters printed n + the number of characters printed
	by putstr with the argument va_arg(args, char *).
		- va_arg(args, char *) returns the next argument in the va_list variable args, that
		means the next arg after the va_start that we did
*/
int ptf(char *s, va_list args, int i, int n)
{
	if (!s[i])
		return n;
	if (s[i] == '%' && s[i + 1] == 's')
		return ptf(s, args, i + 2, n + putstr(va_arg(args, char *)));
	if (s[i] == '%' && s[i + 1] == 'd')
		return ptf(s, args, i + 2, n + putnum(va_arg(args, int), 10));
	if (s[i] == '%' && s[i + 1] == 'x')
		return ptf(s, args, i + 2, n + putnum(va_arg(args, int), 16));
	write(1, &s[i], 1);
	return ptf(s, args, i + 1, n + 1);
}

/*
	on the input, there is a string s and and the three dots are the arguments
	we are passing to the function (in our case, we are passing to the string s 
	"Hello, %s! %d %x\n" and the arguments "world", 42, 42)

	we are creating a va_list variable called args.
	- va_start is a macro that initializes the va_list variable to the first argument
	after the string s - that is the "world" in our case.
	- ptf is a recursive function that takes the string s, the va_list variable args,
	the index i, and the number of characters printed n. It returns the number of
	characters printed.
	- va_end is a macro that cleans up the va_list variable. We have to call it
	because otherwise, we would have a memory leak.
*/
int ft_printf(char *s, ...)
{
	va_list args;
	int		printed_chars;

	va_start(args, s);
	printed_chars = ptf(s, args, 0, 0);
	va_end(args);

	return printed_chars;
}

int main(void)
{
	int	ret_len;

	ret_len = ft_printf("Hello, %s! %d %x\n", "world", 42, 42);
	printf("ret_len: %d\n", ret_len);
	
	ft_printf("Hello, %s! %d %x\n", "world", 10, 10);
	ft_printf("Hello, %s! %d %x\n", "world", 16, 16);
	return EXIT_SUCCESS;
}


/* ********************************************************************************************* */


// #include <stdarg.h>
// #include <unistd.h>
// #include <stdio.h>

// #define DEC 10
// #define HEX 16

// int	putstr(char *str)
// {
// 	int	i;

// 	i = -1;
// 	while(str[++i])
// 		write(1, &str[i], 1);
// 	return i;
// }

// int	putnum(int num, int base)
// {
// 	char	*hd = "0123456789abcdef";

// 	if (num < 0)
// 		return write(1, "-", 1) + putnum(-1 * num, base);
// 	if (num / base == 0)
// 		return write(1, &hd[num % base], 1);
// 	return putnum(num / base, base) + putnum(num % base, base);
// }

// int	ptf(va_list ap, char *str, int i, int n)
// {
// 	if (!str[i])
// 		return n;
// 	if (str[i] == '%' && str[i + 1] == 's')
// 		return ptf(ap, str, i + 2, n + putstr(va_arg(ap, char *)));
// 	if (str[i] == '%' && str[i + 1] == 'd')
// 		return ptf(ap, str, i + 2, n + putnum(va_arg(ap, int), DEC));
// 	if (str[i] == '%' && str[i + 1] == 'x')
// 		return ptf(ap, str, i + 2, n + putnum(va_arg(ap, int), HEX));
// 	write (1, &str[i], 1);
// 	return ptf(ap, str, i + 1, n + 1);
// }

// int	ft_printf(char *str, ...)
// {
// 	va_list	ap;
// 	int		str_len;

// 	va_start(ap, str);
// 	str_len = ptf(ap, str, 0, 0);
// 	va_end(ap);
// 	return str_len;
// }

// int	main()
// {
// 	int	ret_len;

// 	ret_len = printf("Hello, %s and %d aka %x\n", "world", 42, 42);
// 	printf("ret_len: %d\n", ret_len);
// 	ret_len = ft_printf("Hello, %s and %d aka %x\n", "world", 42, 42);
// 	printf("ret_len: %d\n", ret_len);

// 	return 0;
// }