/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvydra <kvydra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 11:44:56 by kvydra            #+#    #+#             */
/*   Updated: 2023/12/30 12:16:50 by kvydra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_UTILS_H
# define LIBFT_UTILS_H

# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

void			*ft_memcpy(void *dest, const void *src, unsigned int n);
char			*ft_strjoin(char const *s1, char const *s2);
unsigned int	ft_strlcpy(char *dst, const char *src, unsigned int size);
int				ft_strlen(char *str);
unsigned int	ft_strlcat(char *dest, char *src, unsigned int size);
void			*ft_memcpy(void *dest, const void *src, unsigned int n);
char			*ft_strcpy(char *dest, char *src);
int				ft_strncmp(char *s1, char *s2, unsigned int n);

#endif