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

#include "../dat.h"
#include "../fns.h"

int
main(void) {
	char consinput[] = "wasd\n";
	char sysoutput[] = "hello world!\n";

	int sys_sock[2];
	socketpair(AF_UNIX, SOCK_STREAM, 0, sys_sock);

	int con_sock[2];
	socketpair(AF_UNIX, SOCK_STREAM, 0, con_sock);

	int confd = con_sock[1], sysfd = sys_sock[1];


	// child proc gets the first entry of both sockets
	int p = fork();
	if (!p) {
		srvCons(con_sock[0], sys_sock[0]);
	}

	// Attach to server
	


}
