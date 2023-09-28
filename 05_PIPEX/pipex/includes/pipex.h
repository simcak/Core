/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 17:17:23 by psimcak           #+#    #+#             */
/*   Updated: 2023/09/28 18:59:08 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

#include <stdio.h> //perror
#include <stdlib.h> // EXIT_FAILURE
#include <unistd.h> //pipe, close, dup, dup2
#include <sys/wait.h> //waitpid, pid_t
#include <fcntl.h> //O_RDONLY, O_WRONLY, O_CREAT, O_TRUNC, open

void	execute(char *argv, char **envp);
void	ft_error(char *str);
void	ft_putstr_fd(char *str, int fd);

#endif