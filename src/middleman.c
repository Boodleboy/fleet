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

void run_middleman(flt_resources resources, flt_proc proc) {
	nfds_t nfds = resources.count + 1;
	struct pollfd* fds = malloc(nfds * sizeof(struct pollfd));

	struct pollfd myfd = { .fd=proc.sock, .events=POLLIN, .revents=0 };
	fds[nfds-1] = myfd;

	for (int i=0;i<resources.count;i++) {
		struct pollfd myfd = { .fd=resources.servers[i].sock, .events=POLLIN, .revents=0 };
		fds[i] = myfd;
	}

	while (true) {
		poll(fds, nfds, -1);
		for (nfds_t i=0;i<nfds;i++) {
			if (fds[i].revents == 0) 
				continue;
			// for now just put all data into cons
			char buf[1];
			read(fds[i].fd, buf, 1);
			write(resources.servers[0].sock, buf, 1); // cons is hardcoded.
													  // Don't forget this
		}
	}
}
