/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 17:17:23 by psimcak           #+#    #+#             */
/*   Updated: 2023/10/04 17:53:23 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

#include <stdio.h> //perror
#include <stdlib.h> // EXIT_FAILURE
#include <unistd.h> //pipe, close, dup, dup2
#include <sys/wait.h> //waitpid, pid_t
#include <fcntl.h> //O_RDONLY, O_WRONLY, O_CREAT, O_TRUNC, open

void	ft_execute(char *argv, char **envp);
void	ft_error(char *str);
void	ft_putstr_fd(char *str, int fd);
char	**ft_split(char const *str2split, char char4split);
char	*ft_strnstr(const char *str, const char *sub_string, size_t len);

#endif