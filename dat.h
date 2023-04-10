typedef struct fltService fltService;
typedef struct fltRunSrv fltRunSrv;
typedef struct flt_resources flt_resources;

typedef struct flt_proc flt_proc;


struct fltService {
	void (*func)(int);
	char* name;
};

struct fltRunSrv {
	char *name;
	pid_t pid;
	int sock;
};

struct flt_resources {
	int count;
	fltRunSrv *servers;
};

struct flt_proc {
	pid_t pid;
	int sock;
};
