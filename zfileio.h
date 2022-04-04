#ifndef ZFILEIO_H
#define ZFILEIO_H

#include "zstring.h"
#include "com.h"
#include <cstdio>
#define _FILE_OFFSET_BITS 64

class ZFileio {
public:
	ZFileio(char *in, char *out)
	{
		fpin  = fopen(in, "rb");
		fpout = fopen(out, "wb");

		zassert(!fpin);
		zassert(!fpout);
	}
	~ZFileio()
	{
		fclose(fpin);
		fclose(fpout);
	}
	
private:
	uint64_t getSize()
	{
		fseeko(fpin, inLen, SEEK_END);
		return SEEK_END;
	}

	FILE *fpin;
	FILE *fpout;

	uint64_t inLen;
};

#endif
