// https://github.com/josephcheel/42-Exam-Rank-06

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/select.h>

#define MAX_MSG_SIZE 1000000
#define MAX_CLIENTS 1024

typedef struct s_client
{
	int	id;
	char	msg[MAX_MSG_SIZE];
}t_client;

t_client clients[MAX_CLIENTS];

int current_id = 0;
int maxfd = 0;

fd_set read_set;
fd_set write_set;
fd_set current;

char	send_buffer[MAX_MSG_SIZE];
char	recv_buffer[MAX_MSG_SIZE];

void putstr(int fd, char *str)
{
	int i = 0;
	while (str[i] != '\0')
	{
		write(fd, &str[i], 1);
		i++;
	}
}

void err(char *msg)
{
	if (!msg)
		putstr(2, "Fatal error\n");
	else
		putstr(2, msg);
	exit(1);
}

void	send_broadcast(int accepted)
{
	for (int fd = 0; fd <= maxfd; fd++)
	{
		if (FD_ISSET(fd, &write_set) && fd != accepted)
			if (send(fd, send_buffer, strlen(send_buffer), 0) == -1)
				err(NULL);
	}
}

int main(int ac, char **av)
{
	if (ac != 2)
		err("Wrong number of arguments\n");
	int sockfd, connfd;
	struct sockaddr_in servaddr; 

	// socket create and verification 
	sockfd = socket(AF_INET, SOCK_STREAM, 0); 
	if (sockfd == -1)
		err(NULL);
	bzero(&servaddr, sizeof(servaddr)); 

	FD_ZERO(&current);
	FD_SET(sockfd, &current);
	maxfd = sockfd;
	
	// assign IP, PORT 
	servaddr.sin_family = AF_INET; 
	servaddr.sin_addr.s_addr = htonl(2130706433); //127.0.0.1
	servaddr.sin_port = htons(atoi(av[1])); 
  
	// Binding newly created socket to given IP and verification 
	if ((bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr))) != 0)
		err(NULL);

	if (listen(sockfd, 10) != 0)
		err(NULL);
	while (1)
	{
		read_set = write_set = current;
		if (select(maxfd + 1, &read_set, &write_set, NULL, NULL) == -1)
			err(NULL);
		for (int fd = 0; fd <= maxfd; fd++)
		{
			if (FD_ISSET(fd, &read_set))
			{
				if (fd == sockfd)
				{
					struct sockaddr_in cli;
					bzero(&cli, sizeof(cli));
					socklen_t len = sizeof(cli);
					connfd = accept(sockfd, (struct sockaddr *)&cli, &len);
					if (connfd < 0)
						err(NULL);
					if (connfd > maxfd)
						maxfd = connfd;
					clients[connfd].id = current_id;
					current_id++;
					FD_SET(connfd, &current);
					sprintf(send_buffer, "server: client %d just arrived\n", clients[connfd].id);
					send_broadcast(connfd);
				}
				else
				{
					int ret = recv(fd, recv_buffer, MAX_MSG_SIZE, 0);
					if (ret <= 0)
					{
						sprintf(send_buffer, "server: client %d just left\n", clients[fd].id);
						send_broadcast(fd);
						FD_CLR(fd, &current);
						close(fd);
					}
					else
					{
						for (int i = 0, j = strlen(clients[fd].msg); i < ret; i++, j++)
						{
							clients[fd].msg[j] = recv_buffer[i];
							if (clients[fd].msg[j] == '\n')
							{
								clients[fd].msg[j] = '\0';
								sprintf(send_buffer, "client %d: %s\n", clients[fd].id, clients[fd].msg);
								send_broadcast(fd);
								bzero(clients[fd].msg, strlen(clients[fd].msg));
								j = -1;
							}
						}
					}
				}
			}
		
		}
	}
	
}
