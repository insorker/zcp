#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include "../zstd/zhash.h"
using namespace std;

int main() {
	srand((unsigned int)time(nullptr));
	const char *s = "abcdabcddcbdab";
	int slen = strlen(s);


	ZHash hash;
	ZString str(s, slen);

	hash.insert(0, str);
	hash.insert(1, str);
	hash.insert(2, str);
	hash.insert(3, str);
	cout << hash.query(4, str).first << ' ' << hash.query(4, str).second<< endl;
	cout << hash.query(5, str).first << ' ' << hash.query(5, str).second<< endl;
	cout << hash.query(9, str).first << ' ' << hash.query(9, str).second<< endl;
	cout << hash.query(11, str).first << ' ' << hash.query(11, str).second<< endl;
	hash.insert(13, str);
	hash.query(2312, str);
}
