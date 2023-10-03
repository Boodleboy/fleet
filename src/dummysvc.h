#include "ixp.h"

void dummy_service(int);

void dummy_version(IxpFVersion*, IxpFcall*);
void dummy_auth(IxpFAttach*, IxpFcall*);
void dummy_attach(IxpFAttach*, IxpFcall*);
void dummy_flush(IxpFTFlush*, IxpFcall*);
void dummy_walk(IxpFTWalk*, IxpFcall*);
void dummy_open(IxpFTCreate*, IxpFcall*);
void dummy_create(IxpFTCreate*, IxpFcall*);
void dummy_read(IxpFIO*, IxpFcall*);
void dummy_write(IxpFIO*, IxpFcall*);

void dummy_remove(IxpFcall*, IxpFcall*);
void dummy_stat(IxpFRStat*, IxpFcall*);
void dummy_wstat(IxpFTWStat*, IxpFcall*);
void dummy_error(IxpFError*, IxpFcall*, char*);
