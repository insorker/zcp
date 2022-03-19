#ifndef ZCP_H
#define ZCP_H

#include <string>
#include <fstream>

class Zcp
{
public:
	typedef enum {
		ZCP_SUCCESS = 0,
		ZCP_ERROR,
	} State;
	// p | 16b | pos relative to c
	// l |  8b | len of match
	// c |  8b | first char after match
	typedef int64_t   int_idx64;
	typedef int32_t   int_idx32;
	typedef int_idx32 int_idx;
	typedef uint32_t  uint_plc;
	typedef int16_t   int_buf;
	typedef int8_t    int_win;

public:
	Zcp(int_win szWin, int_buf szBuf)
		: szWin(szWin), szBuf(szBuf)
	{ }

	State compress(std::string &sig, std::ostream &osfile);
	std::string decompress(std::istream &isfile);

private:
	uint_plc match(std::string &subSig, int_idx cur);

	// szBuf | size of look ahead buffer
	// szWin | size of sliding window
	int_buf szBuf;
	int_win szWin;
};

#endif
