#include <stdio.h>
#include <unistd.h>
#include <check.h>

#include "../src/service.h"

START_TEST (basic) {
	init_service(&dummysvc);

	fail_unless(1 == 1);
}

int 
service_suite()
{
    Suite *s1 = suite_create("Service");
    TCase *tc1_1 = tcase_create("Service");
    SRunner *sr = srunner_create(s1);
    int nf;

    suite_add_tcase(s1, tc1_1);
    tcase_add_test(tc1_1, basic);

    srunner_run_all(sr, CK_ENV);
    nf = srunner_ntests_failed(sr);
    srunner_free(sr);

    return nf == 0 ? 0 : 1;
}
