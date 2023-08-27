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

#include "hashmap.h"
#include "dat.h"
#include "fns.h"

#define PORT 8080

void write_Fcall(IxpFcall, int);
IxpFIO make_twrite(uint32_t, uint64_t, uint32_t, char*);

char *def_version = "9P2000";
fltService services[] = {
	{ .name="console", .func=srvCons }
};

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
		// TODO: write actual 9P fcalls to this fd
		IxpFcall call;
		call.twrite = make_twrite(0, 0, 1, buf);
		
		write(sock[1], buf, 1);
	}
}

void write_Fcall(IxpFcall call, int fd) {
}

void send_fcall(int fd, IxpFcall *call) {
}

IxpFHdr make_hdr(uint8_t type, uint16_t tag, uint32_t fid) {
	IxpFHdr ret;
	ret.type = type;
	ret.tag = tag;
	ret.fid = fid;
	return ret;
}

IxpFcall make_tversion() {
	IxpFcall call;
	IxpFVersion ret;
	ret.hdr = make_hdr(P9_TVersion, 0, 0); // TODO: make actual tag 
	ret.msize = 2000;
	ret.version = def_version;
	call.tversion = ret;
	return call;
}

IxpFIO make_twrite(uint32_t fid, uint64_t offset, uint32_t count, char *data) {
	IxpFIO ret;
	ret.hdr = make_hdr(P9_TWrite, 0, fid);
	ret.offset = offset;
	ret.count = count;
	ret.data = data;
	return ret;
}


