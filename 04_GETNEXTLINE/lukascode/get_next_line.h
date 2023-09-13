/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljiriste <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 11:24:52 by ljiriste          #+#    #+#             */
/*   Updated: 2023/09/11 18:44:28 by ljiriste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 80
# endif

# include <stddef.h>

typedef struct s_file_thread
{
	int		fd;
	char	*buffer;
}			t_ft;

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

char	*get_next_line(int fd);

t_list	*new_ft_node(int fd);
t_list	*ft_lstnew(void *content);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	ft_strncat_alloc(char **dest, char *src, int n);

char	*get_next_line(int fd);

#endif
