#include <iostream>
#include <string>
#include <cstdlib>
#include <cstring>
#include "LZ77.h"
using namespace std;

#define szWin 200
#define szBuf 300

void test_compress() {
	string s = "aacaacabcabaaac";
	LZ77 lz(4, 6);
	vector<PLC> plc;

	plc = lz.compress(s);

	for (int i = 0; i < plc.size(); i ++ ) {
		cout << '(';
		cout << plc[i].p << ", ";
		cout << plc[i].l << ", ";
		cout << plc[i].c << ')';
		cout << endl;
	}
}

void test_decompress() {
	string s = "aacaacabcabaaac";
	LZ77 lz(200, 300);
	vector<PLC> plc;

	plc = lz.compress(s);
	cout << lz.decompress(plc) << endl;
}

static const char state[4] = { '0', '1', 'x', 'z' };
string genStr(int times) {
	int idx;
	string s;

	for (int i = 0; i < times; i ++ ) {
		idx = rand() % 4;
		s.push_back(state[idx]);
	}

	return s;
}

int main(int argc, char *argv[]) {
	srand((unsigned int)time(NULL));

	int randTimes = 0;
	if (argc == 1)
		randTimes = 1000;
	else
		randTimes = atoi(argv[1]);

	string s = genStr(randTimes);
	LZ77 lz(szWin, szBuf);
	vector<PLC> plc;
	plc = lz.compress(s);

	for (int i = 0; i < plc.size(); i ++ ) {
		cout << '(';
		cout << plc[i].p << ", ";
		cout << plc[i].l << ", ";
		cout << plc[i].c << ')';
		cout << endl;
	}
	
	string out = lz.decompress(plc);
	cout << out << endl;

	return 0;
}
