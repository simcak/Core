#include <unistd.h>

unsigned char	reverse_bits(unsigned char octet)
{
	int	i = -1;
	unsigned char	bit;

	while (++i < 8)
	{
		bit = octet >> i & 1;
		bit += '0';
		write (1, &bit, 1);
	}
	write (1, "\n", 1);
	return (bit);
}

int	main(void)
{
	reverse_bits('5');
	return (0);
}