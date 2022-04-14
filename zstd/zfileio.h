#ifndef ZFILEIO_H
#define ZFILEIO_H

#include <cstdio>
#include <cstdint>

#define _FILE_OFFSET_BITS 64

class ZFileio {
public:
	ZFileio(char *file) { }
	~ZFileio() { }
	
protected:
	uint64_t getSize()
	{
		fseeko(fpin, inLen, SEEK_END);
		return SEEK_END;
	}

	uint64_t inLen;
};

#endif
