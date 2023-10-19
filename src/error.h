typedef struct Error Error;

struct Error {
	char *msg;
	int priority;
	bool fatal;
};

int start_err_thread(void);
void log_error(char*, int);
void log_fatal(char*);
void *error_thread(void*);

extern apr_queue_t *log_queue;
extern apr_queue_t *fatal_log_queue;
