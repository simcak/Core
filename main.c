/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 12:31:13 by psimcak           #+#    #+#             */
/*   Updated: 2023/08/15 18:27:30 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <string.h> // knihovna pro memset
#include <strings.h> // knihovna pro bzero

int	main(void)
{
	char	unistr[] = "This is a string!";
	char	src[] = "Hello world!";
	char	dst[10];
	
	printf("FT_ISALPHA: %i 2nd: %i \n", ft_isalpha(77), ft_isalpha(17));
	printf("FT_ISDIGIT: %i 2nd: %i \n", ft_isdigit(100), ft_isdigit(48));
	printf("FT_ISALNUM: %i 2nd: %i \n", ft_isalnum(99), ft_isalnum(57));
	printf("FT_ISASCII: %i 2nd: %i \n", ft_isascii(0), ft_isascii(-257));
	printf("FT_ISPRINT: %i 2nd: %i \n", ft_isprint(50), ft_isprint(112));
	printf("FT_STRLEN: %i \n", ft_strlen("Hello world"));
	printf("FT_MEMSET: %s \n", (char *)ft_memset(unistr, '-', 7));
	
    ft_bzero(unistr, sizeof(unistr));
    printf("FT_BZERO: ");
    for (size_t i = 0; i < sizeof(unistr); i++) {
        if (unistr[i] == '\0') {
            printf("\\0 ");
        } else {
            printf("%c ", unistr[i]);
        }
    }
    printf("\n");
	
	size_t len = ft_strlcpy(dst, src, sizeof(dst));
	printf("FT_STRLCPY len: %zu str: %s \n", len, dst);
	printf("FT_ATOI: %i \n", ft_atoi("--+-321p7"));
	return (0);
}
