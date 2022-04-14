#ifndef ZHASH_H
#define ZHASH_H

#include "zcom.h"
#include "zlisttable.h"
#include "zstring.h"
#include <cstring>
#include <utility>

class ZHash : public ZListTable
{
public:
	void insert(mstr_t mstrp, ZString &mstr);
	std::pair<mstr_t, mstr_t> query(mstr_t mstrp, ZString &mstr);

	bool match(mstr_t &i, mstr_t &j, ZString &str) {
		if (i >= str.size())  return false;
		if (j >= str.size())  return false;
		if (str[i] != str[j]) return false;
		return true;
	}

protected:
	head_t hash(mstr_t x, ZString &str)
	{
		head_t h = 0;
		for (mstr_t i = 0; i < M1; i++) {
			h = (h << S1) ^ str[x++];
			h = h & ZLISTTABLE_HEAD_MASK;
		}
		return h;
	}

private:
	// the minimal size when comparing string
	static const int M1 = 3;
	// h shift
	static const int S1 = 5;
	// the largest size when comparing string
	static const int M2 = BUFF_SIZE;
};

#endif
