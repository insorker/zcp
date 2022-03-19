#define dbg_compress 0
#define dbg_decompress 0
#define dbg_match 0

#include "zcp.h"
#include <iostream>
using std::cerr;
// using std::cout;
using std::endl;
using std::string;
using std::ostream;
using std::istream;

#define PLC_BUFFER_SIZE 1000
#define PLC_WR_CONVER   (sizeof(uint_plc) / sizeof(char))
#define PLC_P_BIAS      16
#define PLC_L_BIAS		8
#define PLC_C_BIAS		0
#define plc_store(plc, plcbuf, plcptr) \
	(plcbuf[plcptr ++ ] = plc)
#define plc_set(p, l, c) \
	(((p) << PLC_P_BIAS) + ((l) << PLC_L_BIAS) + ((c) << PLC_C_BIAS))
#define plc_getp(plc) (((plc) >> PLC_P_BIAS) & 0xFFFF)
#define plc_getl(plc) (((plc) >> PLC_L_BIAS) & 0x00FF)
#define plc_getc(plc) (((plc) >> PLC_C_BIAS) & 0x00FF)

Zcp::State Zcp::compress(string &sig, ostream &osfile)
{
	if (!osfile) {
		cerr << "File Error" << endl;
		return ZCP_ERROR;
	}

	uint_plc plc, plcBuffer[PLC_BUFFER_SIZE];
	int_idx cur = 0, plcPtr = 0;

	while (cur < sig.size()) {
		plc = match(sig, cur);
#if dbg_compress
		cout << '(' << plc_getp(plc) << ' ';
		cout << plc_getl(plc) << ' ';
		cout << (char)plc_getc(plc) << ')' << endl;
#endif

		plc_store(plc, plcBuffer, plcPtr);
		if (plcPtr >= PLC_BUFFER_SIZE) {
			// write into the zcpfile
			osfile.write((char*)plcBuffer, PLC_BUFFER_SIZE * PLC_WR_CONVER);
			plcPtr = 0;
		}

		cur += plc_getl(plc) + 1;
	}
	osfile.write((char*)plcBuffer, plcPtr * PLC_WR_CONVER);

	return ZCP_SUCCESS;
}

string Zcp::decompress(istream &isfile)
{
	if (!isfile) {
		cerr << "File Error" << endl;
		return "";
	}

	uint_plc p, l, c;
	uint_plc plcRBuffer[PLC_BUFFER_SIZE];
	int_idx cur = 0, nbuf;
	string out;

	while (!isfile.eof()) {
		isfile.read((char*)plcRBuffer, PLC_BUFFER_SIZE * PLC_WR_CONVER);
		nbuf = isfile.gcount();
#if dbg_decompress
		cout << nbuf << endl;
#endif

		for (int_idx i = 0; i < nbuf / PLC_WR_CONVER; i ++ ) {
			p = plc_getp(plcRBuffer[i]);
			l = plc_getl(plcRBuffer[i]);
			c = plc_getc(plcRBuffer[i]);
#if dbg_decompress
		cout << '(' << p << ' ';
		cout << l << ' ';
		cout << (char)c << ')' << endl;
#endif

			if (p == 0 && l == 0) {
				out += (char)c;
			}
			else if (p >= l) {
				out += out.substr(cur - p, l);
				out += (char)c;
			}
			else {
				int_idx repeatTimes = l / p;
				int_idx lastLen = l % p;
				for (int_idx i = 0; i < repeatTimes; i ++ ) {
					out += out.substr(cur - p, p);
				}
				out += out.substr(cur - p, lastLen);
				out += (char)c;
			}
			cur += l + 1;
#if dbg_decompress
		cout << out << endl;
#endif
		}
	}

	return out;
}

Zcp::uint_plc Zcp::match(string &subSig, int_idx cur)
{
	int_idx sigBegin = cur - szWin;
	int_idx sigEnd   = cur + szBuf;
	int_idx sigSize  = subSig.size();

	if (sigBegin < 0) sigBegin = 0;
	if (sigEnd > sigSize) sigEnd = sigSize - 1;

	for (int_idx i = sigEnd - cur; i >= 1; i -- ) {
#if dbg_match
		cout << cur << ' ' << i << endl;
#endif
		for (int_idx j = cur - 1; j >= sigBegin; j -- ) {
			string win = subSig.substr(j, i);
			string buf = subSig.substr(cur, i);
#if dbg_match
			cout << win << endl;
			cout << buf << endl;
#endif

			if (win == buf) {
				return plc_set(
					cur - j,
					i,
					subSig[cur + i]
				);
			}
		}
	}
	
	return plc_set(0, 0, subSig[cur]);
}
