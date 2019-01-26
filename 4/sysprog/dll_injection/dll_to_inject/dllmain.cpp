#include <stdio.h>
#include <tchar.h>
#include <assert.h>
#include <windows.h>


BOOL APIENTRY DllMain(
	HMODULE hModule,
	DWORD ul_reason_for_call,
	LPVOID lpReserved
)
{
	switch (ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
			MessageBox(NULL, L"... is loading", L"MyDll", MB_OK);
			//ExitProcess(0);
			break;

		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
			break;

		case DLL_PROCESS_DETACH:
			MessageBox(NULL, L"... is unloading", L"MyDll", MB_OK);
			//system("C:\\Windows\\System32\\notepad.exe");
			break;
	}

	return TRUE;
}

