#include "zlisttable.h"
#include <cstring>

ZListTable::ZListTable()
	: head(new head_t[ZLISTTABLE_HEAD_SIZE]),
	  headsz(new head_t[ZLISTTABLE_HEAD_SIZE]),
	  list(new ZList[SWIN_SIZE])
{
	memset(head, -1, sizeof(head_t) * ZLISTTABLE_HEAD_SIZE);
	memset(headsz, 0, sizeof(head_t) * ZLISTTABLE_HEAD_SIZE);
}

ZListTable::~ZListTable()
{
	delete [] head;
	delete [] headsz;
	delete [] list;
}

void ZListTable::insert(head_t headp, mstr_t mstrp)
{
	mstr_t listp = mstrp & SWIN_MASK;

	if (list[listp].he != -1) {
		headsz[list[listp].he] -- ;
	}

	list[listp].e  = mstrp;
	list[listp].ne = head[headp];
	list[listp].he = headp;

	head[headp]    = listp;
	headsz[headp] ++ ;
}
