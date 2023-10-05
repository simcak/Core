/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   killing_child.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peta <peta@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 20:30:24 by peta              #+#    #+#             */
/*   Updated: 2023/10/02 20:57:36 by peta             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <time.h>
#include <signal.h>

int	main(int argc, char *argv[])
{
	int pid = fork();

	if (pid == -1) 		// Error handling
		return (1);
	
	if (pid == 0) {		// Child process
		while (1) {
			printf("Child executing...\n");
			usleep(50000);
		}
	}
	else {				// Parent process
		sleep(1);
		kill(pid, SIGKILL);
		wait(NULL);
	}
	return 0;
}
