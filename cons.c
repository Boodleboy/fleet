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

void srvCons(int sock) {
	while(true) {
		char buf[100];

		read(sock, buf, 1);

		write(1, buf, 1);
	}
}

