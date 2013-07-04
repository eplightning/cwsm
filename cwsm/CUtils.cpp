#include "CUtils.h"

// Based on www.gamedeception.net/threads/20592-Incredible-optimized-FindPattern
bool CUtils::memoryCompare(const byte* data, const byte* datamask, const char* mask)
{
	for(; *mask; ++data, ++datamask, ++mask)
	{
		if (!strcmp(mask, "xxxx"))
		{
			if (*(uint32*) data != *(uint32*) datamask)
			{
				return FALSE;
			}

			data += 3, datamask += 3, mask += 3;
			continue;
		}

		if (!strcmp(mask, "xx"))
		{
			if (*(uint16*) data != *(uint16*) datamask)
			{
				return FALSE;
			}

			data++, datamask++, mask++;
			continue;
		}

		if (*mask == 'x' && *data != *datamask)
		{
			return false;
		}
	}

	return (*mask) == 0;
}

uptr CUtils::findMemoryAddress(const char* mask, byte* datamask, uptr start, uptr length)
{
	uptr end = start + length;

	for (uptr i = start; i < end; i++)
	{
		if (CUtils::memoryCompare((byte*) i, datamask, mask))
		{
			return i;
		}
	}

	return 0;
}

#ifdef CWSM_PLATFORM_WINDOWS
bool CUtils::modifyProtectedMemory(uptr address, int length, const void* contents)
{
	DWORD old_protect;

	if (!VirtualProtect((LPVOID) address, length, PAGE_EXECUTE_READWRITE, &old_protect))
	{
		return false;
	}

	memcpy((void*) address, contents, length);

	VirtualProtect((LPVOID) address, length, old_protect, &old_protect);

	return true;
}
#endif