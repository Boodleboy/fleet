#include <sys/types.h>
#include <unistd.h>

#include "service.h"

void
init_service(Service *service) {
	int pipes[2];
	
	pipe(pipes);
	pid_t pid = fork();

	if (pid) {
		service->pid = pid;
		service->pipe = pipes[0];
		service->status = 1;
		return;
	}

	(service->func)(pipes[1]);
}
