#include <iostream>
#include <cstdlib>
#include <ctime>
#include "../zhash.h"
using namespace std;

void gen(ZString &str)
{
	// int size = 10;
	// for (int i = 0; i < size; i ++ ) {
	//     str[i] = 'a' + rand() % 26;
	//     cout << str[i];
	// }
	// str.resize(size);
	// cout << endl;
	
	char s[15] = "abcdabcddcbdab";
	str.setstr(s, 15);
}

int main() {
	srand((unsigned int)time(nullptr));

	ZHash hash;
	ZString str;
	gen(str);

	hash.insert(0, str);
	hash.insert(1, str);
	hash.insert(2, str);
	hash.insert(3, str);
	cout << hash.query(4, str).first << ' ' << hash.query(4, str).second<< endl;;
	cout << hash.query(5, str).first << ' ' << hash.query(5, str).second<< endl;;
	cout << hash.query(9, str).first << ' ' << hash.query(9, str).second<< endl;;
	cout << hash.query(11, str).first << ' ' << hash.query(11, str).second<< endl;;
	hash.insert(13, str);
	hash.query(2312, str);
}
