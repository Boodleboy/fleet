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

int init_service(Service *);
// TODO: end_service
int service_send(Service*, IxpFcall*);
int service_recv(Service*, IxpFcall*);
IxpMsg read_message(int, int);
IxpFcall read_fcall(int, int);
int send_fcall(int, int, IxpFcall*);

extern Service dummysvc; 

