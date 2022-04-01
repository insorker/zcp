#ifndef ZHASH_H
#define ZHASH_H

#include "com.h"
#include "zlist.h"
#include "zstring.h"
#include <cstring>
#include <utility>

class ZHash
{
public:
	ZHash()
	{
		head = new hshd_t[ZHASH_HEAD_SIZE];
		headlen = new hshd_t[ZHASH_HEAD_SIZE];
		list = new ZList[ZHASH_ZLIST_SIZE];

		memset(head, -1, sizeof(hshd_t) * ZHASH_HEAD_SIZE);
		memset(headlen, 0, sizeof(hshd_t) * ZHASH_HEAD_SIZE);
	}
	~ZHash()
	{
		delete head;
		delete list;
	}

	void insert(mstr_t p, ZString &mstr)
	{
		hshd_t he = hash(p, mstr);
		int    ls = p & SWIN_MASK;

		list[ls].e  = p;
		list[ls].ne = head[he];
		if (list[ls].he != -1) {
			headlen[he] -- ;
		}
		list[ls].he = he;
		head[he]    = ls;
		headlen[he] ++ ;
	}

	std::pair<mstr_t, mstr_t> query(mstr_t p, ZString &mstr)
	{
		hshd_t he   = hash(p, mstr);
		if (head[he] == -1)
			return std::make_pair(-1, -1);

		mstr_t resp = -1, resl = -1;

		for (int i = head[he], j = 0; j != headlen[he]; i = list[i].ne, j ++ ) {
			mstr_t mstrp = p;
			mstr_t pstrp = list[i].e;
			mstr_t len  = 0;

			while (len < BUFF_SIZE && match(mstrp, pstrp, mstr)) {
				mstrp ++ ; pstrp ++ ; len ++ ;
			}
			if (len > resl) {
				resl = len;
				resp = list[i].e;
			}
		}

		return std::make_pair(resl, resp);
	}

	bool match(mstr_t &i, mstr_t &j, ZString &str) {
		if (i >= str.size())  return false;
		if (j >= str.size())  return false;
		if (str[i] != str[j]) return false;
		return true;
	}

protected:
	hshd_t hash(mstr_t x, ZString &str)
	{
		hshd_t h = 0;
		for (int i = 0; i < M1; i++) {
			h = (h << S1) ^ str[x++];
			h = h & ZHASH_HEAD_MASK;
		}
		return h;
	}

private:
	hshd_t *head;
	hshd_t *headlen;
	ZList  *list;

	// the minimal size when comparing string
	static const int M1 = 3;
	static const int S1 = 5;
	// the largest size when comparing string
	static const int M2 = BUFF_SIZE;
};

#endif
