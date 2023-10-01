#include "dummysvc.h"

typedef struct Service Service;

struct Service {
	void (*func)(int);
	char name[100];
	int status;
	int pid;
	int pipe;
	int msize;
};

void init_service(Service *);
// TODO: end_service
// TODO: service_send
// TODO: service_recv:

extern Service dummysvc; 

