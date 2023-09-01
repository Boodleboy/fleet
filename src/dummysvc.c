#include <stdlib.h>
#include <unistd.h>
#include <ixp.h>

#include "service.h"

void 
dummy_service(int in_pipe) {
	int bsize = 4096;
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
