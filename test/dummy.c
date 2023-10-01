#include <check.h>

#include "suites.h"

START_TEST (dummy_test) {
	fail_unless(1 == 1);
}

void
dummy_tcase(Suite *s) {
	TCase *tc1 = tcase_create("Dummy");

	suite_add_tcase(s, tc1);
	tcase_add_test(tc1, dummy_test);

	return;
}
