/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 12:31:13 by psimcak           #+#    #+#             */
/*   Updated: 2023/08/18 17:53:40 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h> // knihovana pro isprint
#include <string.h> // knihovna pro memset, memmove, memcpy
#include <strings.h> // knihovna pro bzero

int	main(void)
{
	char	unistr[] = "This is a String!";
	char	unistr2[] = "This is a String!";
	char	kukuc = 'S';

	printf("FT_ISALPHA: %i 2nd: %i \n", ft_isalpha(77), ft_isalpha(17));
	printf("FT_TOUPPER: %c 2nd: %c \n", ft_toupper('a'), ft_toupper('7'));
	printf("FT_ISDIGIT: %i 2nd: %i \n", ft_isdigit(100), ft_isdigit(48));
	printf("FT_TOLOWER: %c 2nd: %c \n", ft_tolower('c'), ft_tolower('B'));
	printf("FT_ISALNUM: %i 2nd: %i \n", ft_isalnum(99), ft_isalnum(57));
	printf("FT_STRCHR: %s 2nd: %s STRCHR: %s 2nd: %s \n", 
		ft_strchr("Helllo", 'l'), ft_strchr("42 World", 0), 
		strchr("Helllo", 'l'), strchr("42 World", 0));
	printf("FT_ISASCII: %i 2nd: %i \n", ft_isascii(0), ft_isascii(-257));
	printf("FT_STRRCHR: %s 2nd: %s STRRCHR: %s 2nd: %s \n", 
		ft_strrchr("Helllo", 'l'), ft_strrchr("*42* World", 333), 
		strrchr("Helllo", 'l'), strrchr("*42* World", 333));
	printf("FT_ISPRINT: %i 2nd: %i \n", ft_isprint('~' + 1), isprint('~' + 1));
	printf("FT_STRLEN: %i \n", ft_strlen("Hello world"));
	printf("FT_MEMSET: %s \n", (char *)ft_memset(unistr, '-', 7));
	printf("FT_STRNCMP: %i \n", ft_strncmp("ahoj ", "ahoj", 5));
	
	char *ftmemchrposition = (char *)ft_memchr(unistr2, (int)kukuc, strlen(unistr2));
	char *memchrposition = (char *)memchr(unistr, (int)kukuc, strlen(unistr));
	if (ftmemchrposition)
		printf("FT_MEMCHR: in %td. pos is %c ", ftmemchrposition - unistr2, kukuc);
	else
		printf("FT_MEMCHR: %c not found.", kukuc);
	if (memchrposition)
		printf("MEMCHR: in %td. pos is %c \n", memchrposition - unistr, kukuc);
	else
		printf("MEMCHR: %c not found. \n", kukuc);
	
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
	
	char	sResult[] = {67, 68, 67, 68, 69, 0, 45};
	char	sResult2[] = {67, 68, 67, 68, 69, 0, 45};
	char	ftmemcpysrc[] = "Hello, world!";
	char	ftmemcpydst[20];
	char	memcpysrc[] = "Hello, world!";
	char	memcpydst[20];
	ft_memcpy(ftmemcpydst, ftmemcpysrc, sizeof(ftmemcpydst));
	memcpy(memcpydst, memcpysrc, sizeof(memcpydst));
	printf("FT_MEMCPY: %s MEMCPY: %s \n", ftmemcpydst, memcpydst);
	
	ft_memmove(sResult + 1, sResult, 2);
	memmove(sResult2 + 1, sResult2, 2);
	printf("FT_MEMMOVE: %s MEMMOVE: %s \n", sResult, sResult2);

	char	src1[] = "Hello world!";
	char	dst1[10];
	size_t len1 = ft_strlcpy(dst1, src1, sizeof(dst1));
	printf("FT_STRLCPY len: %zu str: %s \n", len1, dst1);
	
	char	src2[] = "beth";
	char	dest2[8] = "Alpha";
	size_t	len2 = ft_strlcat(dest2, src2, sizeof(dest2));
	printf("FT_STRLCAT: %zu str: %s -> ", len2, dest2);
	printf("size: %zu and dest_len: %d \n", sizeof(dest2), ft_strlen(dest2));
	
	char	src31[] = {-128, 0, 127, 0};
	char	src32[] = {0, 0, 127, 0};
	int		difference1 = ft_memcmp(src32, src31, 1);
	int		difference2 = memcmp(src32, src31, 1);
	printf("FT_MEMCMP: %i MEMCMP: %i \n", difference1, difference2);
	
	printf("FT_STRNSTR: %s STRNSTR: %s \n", 
		ft_strnstr("42Prague school", "Prague", 12), "missing :(");
	
	char	atoivar[] = "0321p7";
	printf("FT_ATOI: %i ATOI: %i \n", ft_atoi(atoivar), atoi(atoivar));

	size_t	num_elements2 = 0;
	int *arr = (int *)ft_calloc(num_elements2, sizeof(int));
	printf("FT_CALLOC: ");
	if (arr == NULL)
	{
		printf("Memory allocation failed \n");
		exit(1);
	}
	for (size_t i = 0; i < num_elements2; i++)
		printf("%d ", arr[i]);
	free(arr);
	
	size_t num_elements = 0;
	int *arr2 = (int *)calloc(num_elements, sizeof(int));
	printf("CALLOC: ");
	if (arr2 == NULL)
	{
		printf("Memory allocation failed \n");
		exit(1);
	}
	for (size_t i = 0; i < num_elements; i++)
		printf("%d ", arr2[i]);
	printf("\n");
	free(arr2);

}
