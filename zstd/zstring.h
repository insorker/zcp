#ifndef ZSTRING_H
#define ZSTRING_H

#include "zcom.h"

#define ZSTRING_SIZE (1 << 20)

class ZString {
public:
	ZString();
	ZString(const char *s, mstr_t len);
	~ZString();
	
	mstr_t size() const;
	void resize(mstr_t sz);

	char &operator[](mstr_t i) const;
	ZString &operator=(const ZString &zstr);

private:
	char *str;
	mstr_t sz;
};

#endif
