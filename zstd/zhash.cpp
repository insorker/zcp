#include "zhash.h"

void ZHash::insert(mstr_t mstrp, ZString &mstr)
{
	head_t headp = hash(mstrp, mstr);
	ZListTable::insert(headp, mstrp);
}

std::pair<mstr_t, mstr_t> ZHash::query(mstr_t mstrp, ZString &mstr)
{
	head_t headp = hash(mstrp, mstr);
	std::pair<mstr_t, mstr_t> result(-1, -1);

	for (swin_t i = head[headp], j = 0; j < headsz[headp]; i = list[i].ne, j ++ ) {
		mstr_t mp		= mstrp;
		mstr_t pp		= list[i].e;
		mstr_t length	= 0;

		while (length < BUFF_SIZE && match(mp, pp, mstr)) {
			mp ++ ; pp ++ ; length ++ ;
		}
		if (length > result.first) {
			result = std::make_pair(length, pp - length);
		}
	}

	return result;
}
