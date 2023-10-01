#include <stdio.h>
#include <unistd.h>
#include <check.h>

#include "../src/service.h"

START_TEST (basic) {
	init_service(&dummysvc);

	fail_unless(1 == 1);
}

void 
service_tcase(Suite *s)
{
    TCase *tc1_1 = tcase_create("Service");

    suite_add_tcase(s, tc1_1);
    tcase_add_test(tc1_1, basic);

	return;
}
