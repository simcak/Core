#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/select.h> // added for fd_set
#include <stdio.h> // added for sprintf

int maxfd, nid;
fd_set cur, rd, wr;
struct { int id; char *buf; } cl[65536];
char sb[65536], rb[65536];

void fatal() { write(2, "Fatal error\n", 12); exit(1); }

void send_all(int x) {
	for (int i = 0; i <= maxfd; i++)
		if (FD_ISSET(i, &wr) && i != x)
			send(i, sb, strlen(sb), 0);
}

int main(int ac, char **av) {
	if (ac != 2) { write(2, "Wrong number of arguments\n", 26); exit(1); }
	int srv = socket(AF_INET, SOCK_STREAM, 0);
	if (srv < 0) fatal();
	struct sockaddr_in a;
	bzero(&a, sizeof(a));
	a.sin_family = AF_INET;
	a.sin_addr.s_addr = htonl(0x7F000001);
	a.sin_port = htons(atoi(av[1]));
	if (bind(srv, (struct sockaddr*)&a, sizeof(a)) < 0) fatal();
	if (listen(srv, 10) < 0) fatal();
	FD_ZERO(&cur);
	FD_SET(srv, &cur);
	maxfd = srv;
	while (1) {
		rd = wr = cur;
		if (select(maxfd + 1, &rd, &wr, 0, 0) < 0) continue;
		for (int fd = 0; fd <= maxfd; fd++) {
			if (!FD_ISSET(fd, &rd)) continue;
			if (fd == srv) {
				int c = accept(srv, 0, 0);
				if (c < 0) continue;
				if (c > maxfd) maxfd = c;
				FD_SET(c, &cur);
				cl[c] = (typeof(cl[c])){nid++, NULL};
				sprintf(sb, "server: client %d just arrived\n", cl[c].id);
				send_all(c);
			} else {
				int n = recv(fd, rb, sizeof(rb) - 1, 0);
				if (n <= 0) {
					sprintf(sb, "server: client %d just left\n", cl[fd].id);
					send_all(fd);
					free(cl[fd].buf);
					FD_CLR(fd, &cur);
					close(fd);
				} else {
					rb[n] = '\0';
					int ol = cl[fd].buf ? strlen(cl[fd].buf) : 0;
					if (!(cl[fd].buf = realloc(cl[fd].buf, ol + n + 1))) fatal();
					strcpy(cl[fd].buf + ol, rb);
					char *s = cl[fd].buf, *p;
					while ((p = strstr(s, "\n"))) {
						*p = '\0';
						sprintf(sb, "client %d: %s\n", cl[fd].id, s);
						send_all(fd);
						s = p + 1;
					}
					char *tmp = calloc(strlen(s) + 1, 1);
					if (!tmp) fatal();
					strcpy(tmp, s);
					free(cl[fd].buf);
					cl[fd].buf = tmp;
				}
			}
		}
	}
}
