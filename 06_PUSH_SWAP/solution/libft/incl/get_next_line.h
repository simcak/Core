/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwoiton <lwoiton@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 13:08:06 by lwoiton           #+#    #+#             */
/*   Updated: 2023/08/16 14:17:47 by lwoiton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

char	*get_next_line(int file_des);
char	*read_and_concat_buff(int filde_des, char *buff);
char	*realloc_buff(char *buff, char *ln_break);
char	*ft_gnl_strjoin(char *left_str, char *buff);
char	*ft_gnl_substr(char *s, char *ln_break);
char	*ft_gnl_strchr(char *s, int c);
size_t	ft_gnl_strlen(char const *c);
size_t	ft_gnl_strlcpy(char *dst, char *src, size_t size);

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# if BUFFER_SIZE < 0
#  undef BUFFER_SIZE
#  define BUFFER_SIZE 0
# endif

# ifndef MAX_FILE_DES
#  define MAX_FILE_DES 1024
# endif
#endif
