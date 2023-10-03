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

#include "ixp.h"
#include "dat.h"
#include "fns.h"

void srvCons(int cons_fd, int sys_fd) {
	while(true) {
		char buf[100];

		read(cons_fd, buf, 1);

		write(sys_fd, buf, 1);
	}
}

