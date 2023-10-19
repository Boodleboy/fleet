#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <apr-1/apr.h>
#include <apr-1/apr_queue.h>

#include <fcntl.h>

#include "error.h"

#define LOGLEVEL 100
#define LOGFILE "fleet.log"
// TODO: set these values in code, not a pp def

apr_queue_t *log_queue, *fatal_log_queue;

Error*
new_error(char *msg, int priority, bool fatal) {
	Error *err = malloc(sizeof(Error));
	err->msg = malloc(strlen(msg)+1); 

	// these mallocs are clunky and slow. apr_pool_t would be better

	strcpy(err->msg, msg);
	err->priority = priority;
	err->fatal = fatal;

	return err;
}

void 
log_error(char *msg, int priority) {
	Error *err = new_error(msg, priority, false);

	apr_status_t stat = APR_EINTR;
	while (stat == APR_EINTR) {
		stat = apr_queue_push(log_queue, err);
	}
}

void
log_fatal(char *msg) {
	Error *err = new_error(msg, 0, true);

	apr_queue_push(log_queue, err);
	// check for message on fatal_log_queue, then exit
	// Need to wait/block on this, otherwise the process could exit before the
	// error is actually logged

	char *ptr = NULL;
	apr_status_t stat = APR_EINTR;
	while (stat == APR_EINTR) {
		stat = apr_queue_pop(fatal_log_queue, (void**)&ptr);
	}

}

int
start_err_thread() {
	apr_pool_t *pool;
	apr_status_t stat;

	stat = apr_pool_create(&pool, NULL);
	if (stat != APR_SUCCESS) {
		return 1;
	}

	char *buf;
	buf = apr_palloc(pool, 32*sizeof(void*));
	buf[0] = 'r';
	buf[1] = '\0';

	stat = apr_queue_create(&log_queue, 32*sizeof(void*), pool);
	if (stat != APR_SUCCESS) {
		return 2;
	}
	stat = apr_queue_create(&fatal_log_queue, 8, pool);
	if (stat != APR_SUCCESS) {
		return 3;
	}

	pthread_t err_thread;
	pthread_create(&err_thread, NULL, error_thread, pool);
	
	return 0;
}

void*
error_thread(void *arg) {
	apr_status_t stat;
	apr_pool_t *pool;
	pool = arg;

	Error *err;

	FILE *fp = fopen(LOGFILE, "a");
	if (fp == NULL) {
		printf("failed to open log file\n");
		return NULL; // where am I gonna send the error to?
	}
	while (true) {
		stat = APR_EINTR;
		while (stat == APR_EINTR) {
			stat = apr_queue_pop(log_queue, (void**)&err);
		}
		if (err->priority <= LOGLEVEL) {
			fwrite(err->msg, strlen(err->msg), 1, fp);
			fwrite("\n", 1, 1, fp);
		}
		if (err->fatal) {
			fclose(fp);
			apr_queue_push(fatal_log_queue, NULL); 
			apr_pool_destroy(pool);
			free(err->msg);
			free(err);
			return NULL;
		}
		free(err->msg);
		free(err);
	}
	return NULL;
}

