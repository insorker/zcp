#ifndef ZLISTTABLE_H
#define ZLISTTABLE_H

#include "zcom.h"
#include "zlist.h"

#define ZLISTTABLE_HEAD_SIZE (1 << 15)
#define ZLISTTABLE_HEAD_MASK (ZLISTTABLE_HEAD_SIZE - 1)

class ZListTable {
public:
	ZListTable();
	~ZListTable();

	void insert(head_t headp, mstr_t mstrp);

protected:
	head_t *head;
	head_t *headsz;
	ZList  *list;
};

#endif
