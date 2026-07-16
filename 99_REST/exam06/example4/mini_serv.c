#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>

//+++++++++ Global variables
int		count = 0, max_fd = 0;
int		ids[99999];
char	*msgs[99999];

fd_set	rfds, wfds, afds;
char	buf_read[99999], buf_write[42];


//+++++++++ fatal error used everywhere (even in the code copied from main.c)
void	fatal_error()
{
	write(2, "Fatal error\n", 12);
	exit(1);
}

//========== Function copied from main.c (with minor change)
int	extract_message(char **buf, char **msg)
{
	char	*newbuf;
	int		i;

	*msg = 0;
	if (*buf == 0)
		return (0);
	i = -1;
	while ((*buf)[++i])
	{
		if ((*buf)[i] == '\n')
		{
			newbuf = calloc(1, sizeof(*newbuf) * (strlen(*buf + i + 1) + 1));
			if (newbuf == 0)
				fatal_error();	//+++++++++ minor change
			strcpy(newbuf, *buf + i + 1);
			*msg = *buf;
			(*msg)[i + 1] = 0;
			*buf = newbuf;
			return (1);
		}
	}
	return (0);
}

//========== Function copied from main.c (with minor change)
char	*str_join(char *buf, char *add)
{
	char	*newbuf;
	int		len;

	if (buf == 0)
		len = 0;
	else
		len = strlen(buf);
	newbuf = malloc(sizeof(*newbuf) * (len + strlen(add) + 1));
	if (newbuf == 0)
		fatal_error();	//+++++++++ minor change
	newbuf[0] = 0;
	if (buf != 0)
		strcat(newbuf, buf);
	free(buf);
	strcat(newbuf, add);
	return (newbuf);
}

//+++++++++ Notify all clients except the author of the message
void	notify_others(int author, char *str)
{
	for (int fd = 0; fd <= max_fd; fd++)
		if (FD_ISSET(fd, &wfds) && fd != author)
			send(fd, str, strlen(str), 0);
}

//+++++++++ Register a new client
void	register_client(int fd)
{
	max_fd = fd > max_fd ? fd : max_fd;
	ids[fd] = count++;
	msgs[fd] = NULL;
	FD_SET(fd, &afds);
	sprintf(buf_write, "server: client %d just arrived\n", ids[fd]);
	notify_others(fd, buf_write);
}

//+++++++++ Remove a client from the list of active clients
void	remove_client(int fd)
{
	sprintf(buf_write, "server: client %d just left\n", ids[fd]);
	notify_others(fd, buf_write);
	free(msgs[fd]);
	FD_CLR(fd, &afds);
	close(fd);
}

//+++++++++ Send all messages from a client to all other clients
void	send_msg(int fd)
{
	char	*msg;

	while (extract_message(&(msgs[fd]), &msg))
	{
		sprintf(buf_write, "client %d: ", ids[fd]);
		notify_others(fd, buf_write);
		notify_others(fd, msg);
		free(msg);
	}
}

//=====++++++++++++ Main function copied from main.c (with major changes)
int	main(int ac, char **av)
{
	int					sockfd, connfd;	//---- removed len var
	struct sockaddr_in	servaddr, cli;

	//+++++++++ Checker added
	if (ac != 2) { return(write(2, "Wrong number of arguments\n", 26), 1); }
	FD_ZERO(&afds);
	//+++++++++

	//========== Copied part from main.c (with minor changes)
	// socket create and verification 
	sockfd = socket(AF_INET, SOCK_STREAM, 0); 
	if (sockfd == -1) { 
		fatal_error();	//+++++++++ minor change
	}
	bzero(&servaddr, sizeof(servaddr)); 

	// assign IP, PORT 
	servaddr.sin_family = AF_INET; 
	servaddr.sin_addr.s_addr = htonl(2130706433); //127.0.0.1
	servaddr.sin_port = htons(atoi(av[1]));	//+++++++++ minor change

	// Binding newly created socket to given IP and verification 
	if ((bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr))) != 0) { 
		fatal_error();	//+++++++++ minor change
	}
	if (listen(sockfd, 10) != 0) {
		fatal_error();	//+++++++++ minor change
	}
	//========== End of copied part from main.c
	//++++++++++ Start of the main loop / major change
	max_fd = sockfd;
	FD_SET(max_fd, &afds);

	while (1)
	{
		rfds = wfds = afds;

		if (select(max_fd + 1, &rfds, &wfds, NULL, NULL) == -1)
			fatal_error();

		for (int fd = 0; fd <= max_fd; fd++)
		{
			if (!FD_ISSET(fd, &rfds))
				continue;

			if (fd == sockfd)
			{
				socklen_t	len = sizeof(cli);
				connfd = accept(sockfd, (struct sockaddr *)&cli, &len);
				if (connfd >= 0)
				{
					register_client(connfd);
					break;
				}
			}
			else
			{
				int	bytes_read = recv(fd, buf_read, 88888, 0);
				if (bytes_read <= 0)
				{
					remove_client(fd);
					break;
				}
				buf_read[bytes_read] = 0;
				msgs[fd] = str_join(msgs[fd], buf_read);
				send_msg(fd);
			}
		}
	}
	return (0);
}
