#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <netdb.h>
#include <unistd.h> 
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>

#define PORT 8080

int main()
{
	int sockfd, connfd, len;
	struct sockaddr_in servaddr, cli;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1) {
		fprintf(stderr, "failed to create socket");
		exit(-1);
	}
	fprintf(stderr, "socket created\n");

	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(PORT);

	if ((bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr))) != 0) {
		fprintf(stderr, "failed to bind socket, errno = %d\n", errno);
		exit(-1);
	}
	fprintf(stderr, "socket bound\n");

	if ((listen(sockfd, 5)) != 0) {
		fprintf(stderr, "listen failed");
		exit(-1);
	}
	len = sizeof(cli);

	connfd = accept(sockfd, (struct sockaddr *)&cli, &len);
	if (connfd < 0) {
		fprintf(stderr, "server failed to accept client");
		exit(-1);
	}
	fprintf(stderr, "server accepted client connection\n");

	char buf[100];

	int n = read(connfd, buf, sizeof(buf));

	fprintf(stderr, "message received: \n");
	for (int i=0;i<n;i++)
		printf("%c", buf[i]);
	printf("\n");

	strcpy(buf, "hiysadfasdfe");
	write(connfd, buf, strlen(buf)+1);

	close(sockfd);
	return 0;
}
