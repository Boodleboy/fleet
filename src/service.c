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
}

int
service_send(Service *s, IxpFcall *icall) {
	char *buf = malloc(s->msize);
	if (buf == NULL) {
		return 1;
	}
	IxpMsg msg = ixp_message(buf, s->msize, MsgUnpack);
	IxpFcall call;
	int msize = ixp_fcall2msg(&msg, &call);
	if (msize == 0) {
		return 1;
		// error
	}

	write(s->pipe, msg.data, msize);
	free(buf);
	return 0;
}

int
service_recv(Service *s, IxpFcall *ocall) {
	return 1;
}
