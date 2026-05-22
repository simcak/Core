#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/select.h> // added for fd_set

int maxfd, nid; // maxfd = biggest fd we need select() to check, nid = next client id

fd_set cur, rd, wr;
// cur -> master set of active sockets
// rd  -> temporary read set for select()
// wr  -> temporary write set for select()

struct { int id; char *buf; } cl[65536];
// cl[fd].id  -> visible client id
// cl[fd].buf -> saved unfinished message for this client

char sb[65536], rb[65536];
// sb -> send buffer
// rb -> receive buffer

void fatal() {
	write(2, "Fatal error\n", 12); // write error to stderr
	exit(1); // stop program with error
}

void send_all(int x) {
	// send current message in sb to every writable socket except x
	// x is usually the sender, so sender does not receive its own message
	for (int i = 0; i <= maxfd; i++)
		if (FD_ISSET(i, &wr) && i != x) // if fd is writable and is not excluded fd
			send(i, sb, strlen(sb), 0); // send sb to this socket
}

int main(int ac, char **av) {
	if (ac != 2) {
		write(2, "Wrong number of arguments\n", 26);
		exit(1);
	}

	// AF_INET  -> IPv4 addresses
	// SOCK_STREAM  -> use TCP
	// 0  -> use the default protocol for socket type (for TCP)
	//        socket(int domain, int type, int protocol);
	int srv = socket(AF_INET, SOCK_STREAM, 0); // fd=3 usually, this is the server socket

	if (srv < 0) fatal();

	struct sockaddr_in a; // IPv4 address structure for bind()
	bzero(&a, sizeof(a)); // clear the whole structure with zeroes

	a.sin_family = AF_INET;  // IPv4 address (it must match the socket type)

	// hton - Host TO Network Long/Short
	a.sin_addr.s_addr = htonl(0x7F000001); // this server listens only on localhost (127.0.0.1)
	a.sin_port = htons(atoi(av[1])); // listen on port from argument

	if (bind(srv, (struct sockaddr*)&a, sizeof(a)) < 0) fatal();
	// after bind() srv is attached to 127.0.0.1:<port>

	if (listen(srv, 10) < 0) fatal();
	// server starts listening, 10 is backlog, not the maximum number of connected clients

	FD_ZERO(&cur);     // clear sockets that the server wants to watch
	FD_SET(srv, &cur); // add server socket to set (srv=3 usually)

	maxfd = srv; // at the start, the biggest fd is only the server socket

	while (1) {
		rd = wr = cur;
		// select modifies fd_sets, so every loop we copy cur into rd and wr again
		// rd asks: who is ready for reading?
		// wr asks: who is ready for writing?

		if (select(maxfd + 1, &rd, &wr, 0, 0) < 0) continue;
		// select waits until something happens on a socket
		// maxfd + 1 -> select checks fds from 0 to maxfd
		// &rd -> after select, rd contains sockets ready to read
		// &wr -> after select, wr contains sockets ready to write
		// 0, 0 -> no error set, no timeout, wait forever
		// if select has error, skip this loop and try again

		for (int fd = 0; fd <= maxfd; fd++) {
			// check every possible fd from 0 to maxfd

			if (!FD_ISSET(fd, &rd)) continue;
			// if this fd is not ready to read, skip it

			if (fd == srv) {
				// server socket is ready to read
				// for server socket this means: new client is waiting

				int c = accept(srv, 0, 0);
				// accept new client
				// srv stays listening
				// c is new socket fd for this client

				if (c < 0) continue; // if accept failed, ignore and continue

				if (c > maxfd) maxfd = c;
				// if new client fd is bigger, update maxfd
				// so select will check this fd in future

				FD_SET(c, &cur);
				// add new client socket to master set
				// from now select watches this client too

				cl[c] = (typeof(cl[c])){nid++, NULL};
				// initialize client data
				// cl[c].id = current nid, then nid++
				// cl[c].buf = NULL because client has no unfinished message yet

				sprintf(sb, "server: client %d just arrived\n", cl[c].id);
				// prepare arrival message in send buffer

				send_all(c);
				// send arrival message to everyone except the new client
			} else {
				// this fd is not the server socket
				// so it is an existing client socket

				int n = recv(fd, rb, sizeof(rb) - 1, 0);
				// receive data from client fd into rb
				// sizeof(rb) - 1 leaves space for '\0'
				// n = number of bytes received
				// n <= 0 means client disconnected or error

				if (n <= 0) {
					// client left or recv error happened

					sprintf(sb, "server: client %d just left\n", cl[fd].id);
					// prepare leaving message

					send_all(fd);
					// tell everyone except this leaving client

					free(cl[fd].buf);
					// free saved unfinished message for this client

					FD_CLR(fd, &cur);
					// remove this client fd from master set
					// select will not watch it anymore

					close(fd);
					// close client socket
				} else {
					// client sent data

					rb[n] = '\0';
					// make received bytes a valid C string

					int ol = cl[fd].buf ? strlen(cl[fd].buf) : 0;
					// ol = old length of saved buffer
					// if there is no old buffer, old length is 0

					if (!(cl[fd].buf = realloc(cl[fd].buf, ol + n + 1))) fatal();
					// resize client buffer to fit:
					// old saved data + new received data + '\0'

					strcpy(cl[fd].buf + ol, rb);
					// append rb after old saved data
					// cl[fd].buf + ol points to the end of old string

					char *s = cl[fd].buf, *p;
					// s points to current position in buffer
					// p will point to found newline

					while ((p = strstr(s, "\n"))) {
						// while there is a complete line ending with '\n'

						*p = '\0';
						// replace newline with '\0'
						// now s is one complete message without the newline

						sprintf(sb, "client %d: %s\n", cl[fd].id, s);
						// prepare message: client id + line

						send_all(fd);
						// send message to everyone except the sender

						s = p + 1;
						// move s after the newline
						// continue checking if there is another complete line
					}

					char *tmp = calloc(strlen(s) + 1, 1);
					// allocate new buffer for remaining unfinished part
					// if s is empty, this creates empty string

					if (!tmp) fatal();

					strcpy(tmp, s);
					// copy unfinished part into tmp

					free(cl[fd].buf);
					// free old bigger buffer

					cl[fd].buf = tmp;
					// save only unfinished part for next recv()
				}
			}
		}
	}
}
