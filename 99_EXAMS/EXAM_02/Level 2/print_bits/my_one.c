#include <unistd.h>

void	print_bits(unsigned char octet)
{
	unsigned int	i = 8;
	unsigned char	bit;

	while (i--)
	{
		bit = octet >> i & 1;
		bit += '0';
		write(1, &bit, 1);
	}
	write(1, "\n", 1);
}

int	main(void)
{
	print_bits('5');
	return (0);
}