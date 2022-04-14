#ifndef ZLIST_H
#define ZLIST_H

#include "zcom.h"

typedef int16_t head_t;

class ZList {
public:	
	ZList()
		: e(-1), ne(-1), he(-1)
	{ }
	mstr_t e;	// value
	swin_t ne;  // next index
	head_t he;  // head index
};

#endif
