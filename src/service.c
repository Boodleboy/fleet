#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#include "service.h"

int
init_service(Service *service) {
	int pipes[2];
	
	pipe(pipes);
	pid_t pid = fork();

	if (pid) {
		service->pid = pid;
		service->pipe = pipes[0];
		service->status = 1;
		return 0;
	}

	(service->func)(pipes[1]);
	exit(0);
	return -1;
}

int
service_send(Service *s, IxpFcall *icall) {
	char *buf = malloc(s->msize);
	if (buf == NULL) {
		return 1;
	}
	IxpMsg msg = ixp_message(buf, s->msize, MsgUnpack);
	int msize = ixp_fcall2msg(&msg, icall);
	if (msize == 0) {
		return 1;
		// error
	}

	write(s->pipe, msg.data, msize);
	free(buf);
	return 0;
}

IxpMsg
read_message(int fd, int bufsize) {
	char *buf = malloc(bufsize);
	uint32_t msize;

	int n = 0;
	while (n < 4) {
		n += read(fd, ((char*)&msize)+n, 4-n);
	}

	n = 0;
	while (n < (int)msize) {
		n += read(fd, buf+n, msize-4-n);
	}
	// TODO: handle errors

	IxpMsg ret = ixp_message(buf, msize, MsgPack);
	return ret;
}

IxpFcall
read_fcall(int fd, int bufsize) {
	IxpFcall ret;

	IxpMsg msg = read_message(fd, bufsize);
	int n = ixp_msg2fcall(&msg, &ret);
	if (n != 0) {
		// error
	}

	free(msg.data);
	return ret;
}




/*
int
service_recv(Service *s, IxpFcall *ocall) {
	return 1;
}
*/
