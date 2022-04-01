#ifndef COM_H
#define COM_H

#include <cstdint>
#include <cassert>

#define zassert(x) assert(x)

typedef int32_t mstr_t;		// main string index
typedef int32_t swin_t;		// sliding window index

const int SWIN_SIZE = 1 << 15;
const int SWIN_MASK = SWIN_SIZE - 1;
const int BUFF_SIZE = 1 << 8;

// SPECIFY FOR ZLIST
// e stores main string index
// ne cannot larger than SWIN_SIZE
typedef mstr_t zle_t;
typedef swin_t zlne_t;

// SPECIFY FOR ZHASH
// ZHASH_HEAD_SIZE is in [0, 1 << 15 -1]
// zlist.size equals SWIN_SIZE
// head is limited in ZHASH_HEAD_SIZE
const int ZHASH_HEAD_SIZE = 1 << 15;
const int ZHASH_HEAD_MASK = ZHASH_HEAD_SIZE - 1;
const int ZHASH_ZLIST_SIZE = SWIN_SIZE;
typedef int16_t hshd_t;

// SPECIFY FOR ZHASH
const int ZSTRING_SIZE = 1 << 20;

#endif
