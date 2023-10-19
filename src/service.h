#include <apr-1/apr.h>
#include <apr-1/apr_queue.h>

#include "dummysvc.h"

typedef struct Service Service;

struct Service {
	void *(*func)(void*);
	char name[100];
	int msize;

	apr_queue_t *iq;
	apr_queue_t *oq;
	int status;
};

int init_service(Service *);
// TODO: end_service
int service_send(Service*, IxpFcall*);
int service_recv(Service*, IxpFcall*);
IxpMsg read_message(int, int);
IxpFcall read_fcall(int, int);
int send_fcall(int, int, IxpFcall*);

extern Service dummysvc; 

