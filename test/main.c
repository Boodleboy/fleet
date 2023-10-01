#include <check.h>

#include "suites.h"

int 
main(void) {

	Suite *s = suite_create("Core");
	SRunner *sr = srunner_create(s);

	int nf = 0;
	dummy_tcase(s);
	service_tcase(s);

    srunner_run_all(sr, CK_ENV);
    nf = srunner_ntests_failed(sr);
    srunner_free(sr);

    return nf == 0 ? 0 : 1;

}
