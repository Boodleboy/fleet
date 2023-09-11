#include <check.h>

START_TEST (test_test) {
	fail_unless(1 == 1);
}

int 
main(void) {
	Suite *s1 = suite_create("Core");
	TCase *tc1 = tcase_create("Core");
	SRunner *sr = srunner_create(s1);
	int nf;

	suite_add_tcase(s1, tc1);
	tcase_add_test(tc1, test_test);

    srunner_run_all(sr, CK_ENV);
    nf = srunner_ntests_failed(sr);
    srunner_free(sr);

    return nf == 0 ? 0 : 1;

}
