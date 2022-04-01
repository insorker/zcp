#ifndef ZLIST_H
#define ZLIST_H

#include "com.h"

class ZList {
public:	
	ZList()
		: e(-1), ne(-1), he(-1)
	{ }
	zle_t e;	// value
	zlne_t ne;  // next index
	hshd_t he;  // head index
};

#endif
