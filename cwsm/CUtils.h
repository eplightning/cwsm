#ifndef _H_CWSM_CUTILS
#define _H_CWSM_CUTILS

#include "global.h"

#include <cstring>

class CUtils {
public:
	static uptr findMemoryAddress(const char* mask, byte* datamask, uptr start, uptr length);
	static bool modifyProtectedMemory(uptr address, int length, const void* contents);

private:
	static bool memoryCompare(const byte* data, const byte* datamask, const char* mask);
};

#endif