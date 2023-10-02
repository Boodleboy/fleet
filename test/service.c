#include <stdio.h>
#include <unistd.h>
#include <check.h>

#include "../src/service.h"

START_TEST (basic) {
	int ret;

	ret = init_service(&dummysvc);
	fail_unless(ret == 0);
	fail_unless(dummysvc.status == 1);

	IxpFcall icall;
	IxpFAttach attach;
	attach.hdr.type = P9_TAttach;
	attach.hdr.tag = 1;
	attach.hdr.fid = 0;
	attach.afid = 2;
	attach.uname = "Dummy";
	attach.aname = "ADummy";
	icall.tattach = attach;
	ret = service_send(&dummysvc, &icall);
	fail_unless(ret == 0);

	/*
	IxpFcall ocall;
	ret = service_recv(&dummysvc, &ocall);
	fail_unless(ret == 0);
	*/

}

void 
service_tcase(Suite *s)
{
    TCase *tc1_1 = tcase_create("Service");

    suite_add_tcase(s, tc1_1);
    tcase_add_test(tc1_1, basic);

	return;
}
