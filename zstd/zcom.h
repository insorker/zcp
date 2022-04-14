#ifndef COM_H
#define COM_H

#include <cstdint>
#include <cstdio>
#include <cassert>

#define zassert(x) assert(x)
#define Zassert(x, s) \
	do { if (!x) { printf("%s: %s", __FILE__, s); assert(x); } } while (0)

typedef int32_t mstr_t;		// main string index
typedef int32_t swin_t;		// sliding window index

const int SWIN_SIZE = 1 << 15;
const int SWIN_MASK = SWIN_SIZE - 1;
const int BUFF_SIZE = 1 << 8;

#endif
