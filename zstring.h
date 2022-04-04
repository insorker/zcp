#ifndef ZSTRING_H
#define ZSTRING_H

#include <cstdint>
#include "com.h"

class ZString {
public:
	ZString()
	{
		str = new char[ZSTRING_SIZE];
	}
	~ZString()
	{
		delete str;
	}

	void setstr(char *str, uint32_t len)
	{
		for (int i = 0; i < len; i ++ ) {
			this->str[i] = str[i];
		}
		this->sz = len;
	}
	
	uint32_t size()
	{
		return sz;
	}
	void resize(uint32_t sz)
	{
		this->sz = sz;
	}

	char &operator[](uint32_t i)
	{
		if (i >= sz) {
			zassert(0);
		}
		return str[i];
	}

private:
	char *str;
	uint32_t sz;
};

#endif
