
typedef struct fltService fltService;
typedef struct fltRunSrv fltRunSrv;


struct fltService {
	void (*func)(int);
	char* name;
};

struct fltRunSrv {
	char *name;
	pid_t pid;
	int sock;
};


