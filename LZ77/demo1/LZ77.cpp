#include "LZ77.h"
#ifndef LZ77_DEBUG
#define LZ77_DEBUG 0
#endif

#if LZ77_DEBUG
#include <iostream>
using namespace std;
#define DB_DECOMP 1
#endif

vector<PLC> LZ77::compress(string &str)
{
	PLC plc;
	LL i = 0;
	vector<PLC> out;

	while (i < str.size()) {
		plc = match(str, i);
		out.push_back(plc);
		i = plc.l + i + 1;
	}

	return out;
}

string LZ77::decompress(vector<PLC> &cp)
{
	LL cur = 0;
	string out;

	for (auto &u : cp) {
		if (u.p == 0 && u.l == 0) {
			out += u.c;
		}
		else if (u.p >= u.l) {
			out += out.substr(cur - u.p, u.l);
			out += u.c;
		}
		else {
			LL repeat = u.l / u.p;
			LL last = u.l % u.p;
			for (LL i = 0; i < repeat; i ++ )
				out += out.substr(cur - u.p, u.p);
			out += out.substr(cur - u.p, last);
			out += u.c;
		}
#if DB_DECOMP
		cout << out << endl;
#endif
		cur += u.l + 1;
	}
	return out;
}

PLC LZ77::match(string &str, LL cur)
{
	LL strBegin = cur - szWin;
	LL strEnd   = cur + szBuf;

	if (strBegin < 0) strBegin = 0;
	if (strEnd > str.size()) strEnd = str.size();

	for (LL i = strEnd - cur; i >= 1; i -- ) {
		for (LL j = strBegin; j < cur; j ++ ) {
			string win = str.substr(j, i);
			string buf = str.substr(cur, i);

			if (win == buf)
				return { cur - j, i, str[cur + i] };
		}
	}
	
	return { 0, 0, str[cur] };
}
