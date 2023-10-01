#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

#include "service.h"

#define MSZ 4096;

Service dummysvc = (Service){
	.name = "dummy",
	.func = dummy_service
};

void 
dummy_service(int in_pipe) {
	int bsize = MSZ;
	char *buf = malloc(bsize);
	int n;
	IxpMsg msg;
	IxpFcall call, resp;

	while (1) {
		n = read(in_pipe, buf, bsize);
		msg = ixp_message(buf, bsize, MsgPack);
		int msize = ixp_msg2fcall(&msg, &call);
		if (msize == 0) {
			// error
		}
		switch (call.hdr.type) {
			P9_TVersion:
				break;
			P9_TAuth:
				break;
			P9_TAttach:
				break;
			P9_TError:
				break;
			P9_TFlush:
				break;
			P9_TWalk:
				break;
			P9_TOpen:
				break;
			P9_TCreate:
				break;
			P9_TRead:
				break;
			P9_TWrite:
				break;
			P9_TClunk:
				break;
			P9_TRemove:
				break;
			P9_TStat:
				break;
			P9_TWStat:
				break;

			P9_RVersion:
			P9_RAuth:
			P9_RAttach:
			P9_RError:
			P9_RFlush:
			P9_RWalk:
			P9_ROpen:
			P9_RCreate:
			P9_RRead:
			P9_RWrite:
			P9_RClunk:
			P9_RRemove:
			P9_RStat:
			P9_RWStat:
			default:
				// error, shouldn't be getting these types
				break;
		}

	}
}

// need wrapper to set tag and send message for each response
void
dummy_version(IxpFVersion *icall, IxpFcall *ocall) {
	IxpFVersion oversion;
	oversion.hdr.type = P9_RVersion;
	oversion.msize = MSZ;

	// TODO: malloc wrapper func?
	oversion.version = malloc(20); 

	strcpy(oversion.version, "9P2000");
}

/*
void
dummy_auth(IxpFAttach *icall, IxpFcall *ocall) {
}

void
dummy_attach(IxpFAttach *icall, IxpFcall *ocall) {
}

void
dummy_flush(IxpFTFlush *icall, IxpFcall *ocall) {
}

void
dummy_walk(IxpFTWalk *icall, IxpFcall *ocall) {
}

void
dummy_open(IxpFcall *icall, IxpFcall *ocall) {
}

void
dummy_create(IxpFcall *icall, IxpFcall *ocall) {
}

void
dummy_read(IxpFcall *icall, IxpFcall *ocall) {
}

void
dummy_write(IxpFcall *icall, IxpFcall *ocall) {
}

void
dummy_clunk(IxpFcall *icall, IxpFcall *ocall) {
}

void
dummy_remove(IxpFcall *icall, IxpFcall *ocall) {
}

void
dummy_stat(IxpFcall *icall, IxpFcall *ocall) {
}

void
dummy_wstat(IxpFcall *icall, IxpFcall *ocall) {
}

void
dummy_error(IxpFcall *icall, IxpFcall *ocall, char *err) {
}
*/
