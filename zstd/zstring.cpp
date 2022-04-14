#include "zstring.h"
#include "zcom.h"

ZString::ZString()
	: str(new char[ZSTRING_SIZE])
{
}

ZString::ZString(const char *s, mstr_t len)
	: str(new char[ZSTRING_SIZE])
{
	resize(len);
	for (mstr_t i = 0; i < len; i ++ ) {
		str[i] = s[i];
	}
}

ZString::~ZString()
{
	delete [] str;
}

mstr_t ZString::size() const
{
	return sz;
}

void ZString::resize(mstr_t sz)
{
	sz = sz;
}

char &ZString::operator[](mstr_t i) const
{
	return str[i];
}

ZString &ZString::operator=(const ZString &zstr) {
	resize(zstr.size());
	for (mstr_t i = 0; i < zstr.size(); i ++ ) {
		str[i] = zstr[i];
	}
	return *this;
}
