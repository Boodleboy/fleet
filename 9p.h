#ifndef IXPLIB
#define IXPLIB
#include <stdint.h>

enum {
	IXP_MAX_VERSION = 32,
	IXP_MAX_MSG = 8192,
	IXP_MAX_ERROR = 128,
	IXP_MAX_CACHE = 32,
	IXP_MAX_FLEN = 128,
	IXP_MAX_ULEN = 32,
	IXP_MAX_WELEM = 16,
};

typedef union Fcall	Fcall;
typedef struct IxpFHdr		IxpFHdr;
typedef struct IxpFError	IxpFError;
typedef struct IxpFROpen	IxpFRAttach;
typedef struct IxpFRAuth	IxpFRAuth;
typedef struct IxpFROpen	IxpFRCreate;
typedef struct IxpFROpen	IxpFROpen;
typedef struct IxpFIO		IxpFRRead;
typedef struct IxpFRStat	IxpFRStat;
typedef struct IxpFVersion	IxpFRVersion;
typedef struct IxpFRWalk	IxpFRWalk;
typedef struct IxpFAttach	IxpFTAttach;
typedef struct IxpFAttach	IxpFTAuth;
typedef struct IxpFTCreate	IxpFTCreate;
typedef struct IxpFTFlush	IxpFTFlush;
typedef struct IxpFTCreate	IxpFTOpen;
typedef struct IxpFIO		IxpFTRead;
typedef struct IxpFVersion	IxpFTVersion;
typedef struct IxpFTWalk	IxpFTWalk;
typedef struct IxpFIO		IxpFTWrite;
typedef struct IxpFTWStat	IxpFTWStat;
typedef struct IxpFAttach	IxpFAttach;
typedef struct IxpFIO		IxpFIO;
typedef struct IxpFVersion	IxpFVersion;

typedef struct IxpQid IxpQid;
typedef struct IxpStat IxpStat;

void fcall2msg(char*, Fcall);
void msg2fcall(char*, Fcall);

struct IxpQid {
	uint8_t		type;
	uint32_t	version;
	uint64_t	path;
	/* Private members */
	uint8_t		dir_type;
};

/* stat structure */
struct IxpStat {
	uint16_t	type;
	uint32_t	dev;
	IxpQid		qid;
	uint32_t	mode;
	uint32_t	atime;
	uint32_t	mtime;
	uint64_t	length;
	char*	name;
	char*	uid;
	char*	gid;
	char*	muid;
};

struct IxpFHdr {
	uint8_t		type;
	uint16_t	tag;
	uint32_t	fid;
};
struct IxpFVersion {
	IxpFHdr		hdr;
	uint32_t	msize;
	char*		version;
};
struct IxpFTFlush {
	IxpFHdr		hdr;
	uint16_t	oldtag;
};
struct IxpFError {
	IxpFHdr		hdr;
	char*		ename;
};
struct IxpFROpen {
	IxpFHdr		hdr;
	IxpQid		qid; /* +Rattach */
	uint32_t	iounit;
};
struct IxpFRAuth {
	IxpFHdr		hdr;
	IxpQid		aqid;
};
struct IxpFAttach {
	IxpFHdr		hdr;
	uint32_t	afid;
	char*		uname;
	char*		aname;
};
struct IxpFTCreate {
	IxpFHdr		hdr;
	uint32_t	perm;
	char*		name;
	uint8_t		mode; /* +Topen */
};
struct IxpFTWalk {
	IxpFHdr	hdr;
	uint32_t	newfid;
	uint16_t	nwname;
	char*		wname[IXP_MAX_WELEM];
};
struct IxpFRWalk {
	IxpFHdr		hdr;
	uint16_t	nwqid;
	IxpQid		wqid[IXP_MAX_WELEM];
};
struct IxpFIO {
	IxpFHdr		hdr;
	uint64_t	offset; /* Tread, Twrite */
	uint32_t	count; /* Tread, Twrite, Rread */
	char*		data; /* Twrite, Rread */
};
struct IxpFRStat {
	IxpFHdr		hdr;
	uint16_t	nstat;
	uint8_t*	stat;
};
struct IxpFTWStat {
	IxpFHdr		hdr;
	IxpStat		stat;
};

union Fcall {
	IxpFHdr		hdr;
	IxpFVersion	version;
	IxpFVersion	tversion;
	IxpFVersion	rversion;
	IxpFTFlush	tflush;
	IxpFROpen	ropen;
	IxpFROpen	rcreate;
	IxpFROpen	rattach;
	IxpFError	error;
	IxpFRAuth	rauth;
	IxpFAttach	tattach;
	IxpFAttach	tauth;
	IxpFTCreate	tcreate;
	IxpFTCreate	topen;
	IxpFTWalk	twalk;
	IxpFRWalk	rwalk;
	IxpFTWStat	twstat;
	IxpFRStat	rstat;
	IxpFIO		twrite;
	IxpFIO		rwrite;
	IxpFIO		tread;
	IxpFIO		rread;
	IxpFIO		io;
};

#endif
