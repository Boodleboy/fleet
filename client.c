#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <strings.h> 
#include <netdb.h>
#include <unistd.h> 
#include <sys/socket.h>
#include <arpa/inet.h> 
#include <poll.h>
#include <ixp.h>

#include "dat.h"
#include "fns.h"
#include "config.h"

#define PORT 8080

void srvCons(int sock) {
	// one way for now
	while(true) {
		char buf[100];

		read(sock, buf, 1);

		write(1, buf, 1);
	}
}

fltRunSrv init_service(fltService srvc) {
	fltRunSrv ret;
	char *name = srvc.name;

	ret.name = malloc(strlen(name)+1);
	strcpy(ret.name, name);
	
	int sock[2];
	socketpair(AF_UNIX, SOCK_STREAM, 0, sock);
	ret.sock = sock[0];

	if (ret.pid = fork()) {
		return ret;
	}
	srvc.func(sock[1]);
	exit(0);
}

flt_resources init_services() {
	int sock[2];
	flt_resources ret;

	ret.count = sizeof(services) / sizeof(services[0]);
	ret.servers = malloc(sizeof(fltRunSrv*) * (ret.count));

	for (int i=0;i<ret.count;i++) {
		ret.servers[i] = init_service(services[i]);
	}

	return ret;
}

flt_proc create_proc() {
	flt_proc ret;
	int sock[2];

	socketpair(AF_UNIX, SOCK_STREAM, 0, sock);
	ret.pid = fork();
	if (!ret.pid) {
		ret.sock = sock[0];
		return ret;
	}
	// this is the child process. Right now it'll just read keyboard and write
	// to a pipe, which writes to the screen. 
	while (true) {
		char buf[100];
		read(0, buf, 1);

		write(sock[1], buf, 1);
	}
}

int main()
{
	// Remove all of this server-client stuff for now. Without a bare minimum
	// client the server is worthless.
	
	/*
	int sockfd, connfd;
	struct sockaddr_in servaddr, cli;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1) {
		fprintf(stderr, "failed to create socket");
		exit(-1);
	}
	fprintf(stderr, "made socket\n");

	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	servaddr.sin_port = htons(PORT);

	if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) != 0) {
		fprintf(stderr, "failed to connect to server");
		exit(-1);
	}
	fprintf(stderr, "connected to server\n");

	*/


	flt_resources resources = init_services();
	flt_proc proc = create_proc();

	nfds_t nfds = resources.count + 1;
	struct pollfd* fds = malloc(nfds * sizeof(struct pollfd));

	struct pollfd myfd = { .fd=proc.sock, .events=POLLIN, .revents=0 };
	fds[nfds-1] = myfd;

	for (int i=0;i<resources.count;i++) {
		struct pollfd myfd = { .fd=resources.servers[i].sock, .events=POLLIN, .revents=0 };
		fds[i] = myfd;
	}

	while (true) {
		int n = poll(fds, nfds, -1);
		for (int i=0;i<nfds;i++) {
			if (fds[i].revents == 0) 
				continue;
			// for now just put all data into cons
			char buf[1];
			read(fds[i].fd, buf, 1);
			write(resources.servers[0].sock, buf, 1); // cons is hardcoded.
													  // Don't forget this
		}
	}

	/*
	char buf[100] = "hellooooo";

	write(sockfd, buf, strlen(buf)+1);

	

	fprintf(stderr, "message sent\n");

	int n = read(sockfd, buf, sizeof(buf));
	fprintf(stderr, "message recieved:\n");
	for (int i=0;i<n;i++)
		fprintf(stderr, "%c", buf[i]);
	fprintf(stderr, "\n");

	fprintf(stderr, "closing socket\n");

	close(sockfd);
	*/
	return 0;
}
