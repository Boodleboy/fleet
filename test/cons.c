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

	int rval;

	// Attach to server
	IxpFcall version = make_tversion();
	int msgsize = 4096;
	char *msgdat = malloc(msgsize);
	printf("about to call ixp_message\n");
	IxpMsg msg = ixp_message(msgdat, msgsize, MsgPack);

	printf("about to fcall2msg\n");
	rval = ixp_fcall2msg(&msg, &version);
	
	printf("fcall2msg val = %d\n", rval);
	rval = ixp_sendmsg(confd, &msg);
	printf("sendmsg val = %d\n", rval);

	rval = ixp_recvmsg(confd, &msg);
	printf("recvmsg val = %d\n", rval);

	


}
