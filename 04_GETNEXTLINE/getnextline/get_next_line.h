/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 11:31:26 by psimcak           #+#    #+#             */
/*   Updated: 2023/09/20 17:05:46 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>

char		*get_next_line(int fd);
void		*ft_calloc(size_t nmemb, size_t size);
char		*ft_strjoin(char const *str1, char const *str2);
int			ft_strlen(const char *str);
char		*ft_strchr(const char *str, int character);
char		*ft_join_and_free(char *str1, char *str2);

#endif

/*
	fcntl lib 	=> open - forbitten function
	unistd lib 	=> close - forbitten function
				=> read - OK func
	OPEN decimals
		0 = no rights
		1 = execute rights
		2 = write rights
		4 = read rights
		7 = write & execute rights
		three numbers: owner|group|others
*/