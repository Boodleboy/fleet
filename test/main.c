#include <check.h>

#include "suites.h"

int 
main(void) {

	int nf = 0;
	nf += dummy_suite();

    return nf == 0 ? 0 : 1;

}
