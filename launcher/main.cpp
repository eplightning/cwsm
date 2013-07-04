#define WIN32_LEAN_AND_MEAN
#include <windows.h>

const char* DLL_NAME = "cwsm.dll";

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	STARTUPINFO startup_info;
	PROCESS_INFORMATION process_info;

	memset(&startup_info, 0, sizeof(STARTUPINFO));
	startup_info.cb = sizeof(startup_info);
	
	if (CreateProcess(TEXT("Server.exe"), NULL, NULL, NULL, TRUE, CREATE_SUSPENDED, NULL, NULL, &startup_info, &process_info))
	{
		LPVOID load_library = (LPVOID) GetProcAddress(GetModuleHandle(TEXT("kernel32.dll")), "LoadLibraryA");
		LPVOID remote_string = (LPVOID) VirtualAllocEx(process_info.hProcess, NULL, strlen(DLL_NAME) + 1, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);

		WriteProcessMemory(process_info.hProcess, remote_string, DLL_NAME, strlen(DLL_NAME) + 1, NULL);

		HANDLE thread = CreateRemoteThread(process_info.hProcess, NULL, NULL, (LPTHREAD_START_ROUTINE) load_library, remote_string, CREATE_SUSPENDED, NULL);

		if (thread == NULL)
		{
			return 1;
		}

		ResumeThread(process_info.hThread);
		ResumeThread(thread);

		CloseHandle(process_info.hProcess);
		CloseHandle(process_info.hThread);
		CloseHandle(thread);

		return 0;
	}

	return 1;
}