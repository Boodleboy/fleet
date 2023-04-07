#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <strings.h> 
#include <netdb.h>
#include <unistd.h> 
#include <sys/socket.h>
#include <arpa/inet.h> 

#define PORT 8080

int init_services() {
	int sock[2];
	int ret = socketpair(AF_UNIX, SOCK_STREAM, 0, sock);
	if (!fork()) {
		return sock[0];
	}

	while (true) {
		char buf[100];
		int n = read(sock[1], buf, 1);
		printf("%c", buf[0]);
	}
}

int create_proc() {
	int sock[2];
	int ret = socketpair(AF_UNIX, SOCK_STREAM, 0, sock);
	if (!fork()) {
		return sock[0];
	}
	// this is the child process. Right now it'll just read keyboard and write
	// to a pipe, which writes to the screen. 
	while (true) {
		char c = getchar();
		write(sock[1], &c, 1);
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

	int procsock = create_proc();
	int servsock = init_services();

	while (true) {
		char buf[100];
		int n = read(procsock, buf, 1);
		write(servsock, buf, 1);
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
