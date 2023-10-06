/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 17:17:23 by psimcak           #+#    #+#             */
/*   Updated: 2023/10/06 20:52:52 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <fcntl.h>

char	*ft_find_paths(char **envp);
char	*ft_final_path(char **splited_paths, char **cmd);
void	ft_error(char *str);
void	ft_putstr_fd(char *str, int fd);
char	**ft_split(char const *str2split, char char4split);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strnstr(const char *str, const char *sub_string, size_t len);
void	ft_free_array_of_strings(char **str);
int		ft_error_police(char *argv, char **envp);

#endif

// <stdio.h> -> perror
// <stdlib.h> -> EXIT_FAILURE
// <unistd.h> -> pipe, close, dup, dup2
// <sys/wait.h> -> waitpid, pid_t
// <fcntl.h> -> O_RDONLY, O_WRONLY, O_CREAT, O_TRUNC, open