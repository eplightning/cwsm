#include "global.h"

#include <iostream>

#include "CUtils.h"

const char MAX_PLAYERS = 127;

// just a quick code to change max players to 127
BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	if (ul_reason_for_call == DLL_PROCESS_ATTACH)
	{
		uptr server_base = (uptr) GetModuleHandle(TEXT("Server.exe"));

		byte max_players_mask[] = { 0xFF, 0x15, 0x00, 0x00, 0x00, 0x00, 0x8B, 0xC8, 0xFF, 0x15, 0x00, 0x00, 0x00, 0x00, 0x83, 0xBD, 0x6C, 0xFE, 0xFF, 0xFF, 0x04 };

		uptr max_players_addr = CUtils::findMemoryAddress("xx????xxxx????xxxxxxx", max_players_mask, (server_base + 0x25000), 0x3000);

		max_players_addr += 20;

		if (max_players_addr != 0)
		{
			char* max_players = (char*) max_players_addr;

			std::cout << "CWSM: max_players found, value: " << (int) *max_players << std::endl;

			CUtils::modifyProtectedMemory(max_players_addr, 1, &MAX_PLAYERS);

			std::cout << "CWSM: max_players set to " << (int) *max_players << std::endl;
		}
		else
		{
			std::cout << "CWSM: max_players address not found" << std::endl;
		}
	}
}