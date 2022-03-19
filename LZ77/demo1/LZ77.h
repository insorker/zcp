#ifndef LZ77_H
#define LZ77_H

#include <string>
#include <vector>
using std::string;
using std::vector;

typedef struct
{
	// p | pos relative to c
	// l | len of match
	// c | idx of char after match
	long long p, l;
	char c;
} PLC;

class LZ77
{
	typedef long long LL;

public:
	LZ77(LL szBuf, LL szWin)
		: szBuf(szBuf), szWin(szWin)
		{ }

	vector<PLC> compress(string &str);
	string decompress(vector<PLC> &cp);

private:
	PLC match(string &str, LL cur);

	// szBuf | size of look ahead buffer
	// szWin | size of sliding window
	LL szBuf, szWin;
};

#endif
