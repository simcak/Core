#include <unistd.h>

unsigned char	swap_bits(unsigned char octet)
{
	int				i;
	unsigned char	bit;

	i = 4;
	while (i--)
	{
		bit = (octet >> i & 1) + '0';
		write (1, &bit, 1);
	}
	i = 8;
	while (--i > 3)
	{
		bit = (octet >> i & 1) + '0';
		write (1, &bit, 1);
	}
	write (1, "\n", 1);
	return (bit);
}

int	main(void)
{
	//		0011 0101
	swap_bits('5');
	return (0);
}