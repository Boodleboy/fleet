#include <check.h>

#include "suites.h"

START_TEST (dummy_test) {
	fail_unless(1 == 1);
}

int
dummy_suite() {
	Suite *s1 = suite_create("Dummy");
	TCase *tc1 = tcase_create("Dummy");
	SRunner *sr = srunner_create(s1);
	int nf;

	suite_add_tcase(s1, tc1);
	tcase_add_test(tc1, dummy_test);

    srunner_run_all(sr, CK_ENV);
    nf = srunner_ntests_failed(sr);
    srunner_free(sr);

    return nf == 0 ? 0 : 1;
}
