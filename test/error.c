#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <check.h>
#include <pthread.h>
#include <apr-1/apr.h>
#include <apr-1/apr_queue.h>

#include "suites.h"
#include "../src/error.h"

#define BUFSIZE 1024

START_TEST (error_test) {
	apr_initialize();

	remove("fleet.log");

	int val = start_err_thread();
	fail_unless(val == 0);

	log_error("test error #1", 1);
	log_error("test error #2", 1);
	log_error("test error #3", 150); // should not output
	
	log_fatal("fatal error");
	char *buf = malloc(BUFSIZE);
	FILE *fp = fopen("fleet.log", "r");

	fail_unless(fp != NULL);

	size_t size = BUFSIZE;

	getline(&buf, &size, fp);
	fail_unless(strcmp(buf, "test error #1\n") == 0);

	getline(&buf, &size, fp);
	fail_unless(strcmp(buf, "test error #2\n") == 0);

	getline(&buf, &size, fp);
	fail_unless(strcmp(buf, "fatal error\n") == 0);
}

void
error_tcase(Suite *s) {
	TCase *tc1 = tcase_create("Error");

	suite_add_tcase(s, tc1);
	tcase_add_test(tc1, error_test);

	return;
}
