#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <cstring>
#include "zcp.h"
using namespace std;

const Zcp::int_win szWin = (Zcp::int_win)100;
const Zcp::int_buf szBuf = (Zcp::int_buf)25;

static const char state[4] = { '0', '1', 'x', 'z' };

string genStr(int times);
void test_base_compress(string s);
string test_base_decompress();

void test_accurate(int times);
void test_cprate_compress(int times);

int main(int argc, char *argv[]) {
	int times = 1;
	if (argc > 1)
		times = atoi(argv[1]);

	// test_cprate_compress(times);
	test_accurate(times);

	return 0;
}

string genStr(int times) {
	int idx;
	string s;

	srand((unsigned int)time(NULL));

	for (int i = 0; i < times; i ++ ) {
		idx = rand() % 4;
		s.push_back(state[idx]);
	}

	return s;
}

void test_base_compress(string s) {
	fstream fs("__test_out.zcp", ios::out | ios::binary);

	Zcp lz(szWin, szBuf);
	lz.compress(s, fs);
}

void test_cprate_compress(int times) {
	srand((unsigned int)time(NULL));

	string str = genStr(times);
	fstream fs("__test_in.txt", ios::out);
	fs << str;
	test_base_compress(str);
}

string test_base_decompress() {
	fstream fs("__test_out.zcp", ios::in | ios::binary);
	
	Zcp lz(szWin, szBuf);
	return lz.decompress(fs);
}

void test_accurate(int times) {
	string sin = genStr(times);

	test_base_compress(sin);
	string sout = test_base_decompress();

	if (sin == sout) {
		cout << "Correct" << endl;
	}
	else {
		cout << "Fault" << endl;
	}
}
