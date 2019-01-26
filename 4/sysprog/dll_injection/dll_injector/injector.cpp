#include <windows.h>
#include <tlhelp32.h>
#include <tchar.h>
#include <stdio.h>
#include <wchar.h>
#include <assert.h>


void GetInputArgs(
	int argc,
	PWCHAR argv[],
	PWCHAR pathToDLL,
	PWCHAR remoteProcessName
);

DWORD GetProcessIDByName(const PWCHAR processName);

LPVOID WritePathToDLLToRemoteProcess(
	HANDLE remoteProcessHandler,
	const PWCHAR pathToDll
);
void LoadDLLToRemoteProcess(
	HANDLE remoteProcessHandle,
	LPVOID pathToDLLRemoteAddress
);

void printError(TCHAR* msg);
void ExitProgram(const int errorCode);



int wmain(int argc, PWCHAR argv[])
{
	WCHAR pathToDLL[MAX_PATH + 1] = {};
	WCHAR remoteProcessName[MAX_PATH + 1] = {};
	GetInputArgs(argc, argv, pathToDLL, remoteProcessName);

	DWORD pid = GetProcessIDByName((PWCHAR)remoteProcessName);
	if (pid == 0)
	{
		wprintf(L"Could not find process '%s'\n", remoteProcessName);
		ExitProgram(1);
	}

	HANDLE remoteProcessHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
	if (remoteProcessHandle == NULL)
	{
		wprintf(L"Could not open process '%s'\n", remoteProcessName);
		ExitProgram(1);
	}

	LPVOID pathToDLLRemoteAddress = WritePathToDLLToRemoteProcess(
		remoteProcessHandle,
		(PWCHAR)pathToDLL
	);

	LoadDLLToRemoteProcess(remoteProcessHandle, pathToDLLRemoteAddress);

	wprintf(
		L"'%s' has been successfully injected to process '%s'\n",
		pathToDLL,
		remoteProcessName
	);

	CloseHandle(remoteProcessHandle);
	system("pause");
	return 0;
}



void GetInputArgs(int argc, PWCHAR argv[], PWCHAR pathToDLL, PWCHAR remoteProcessName)
{
	assert(argv);
	assert(pathToDLL);
	assert(remoteProcessName);

	if (argc == 3)
	{
		if (wcslen(argv[1]) > MAX_PATH || wcslen(argv[2]) > MAX_PATH)
		{
			wprintf(L"Too long arguments. Exiting ...\n");
			ExitProgram(1);
		}

		memcpy((PVOID)pathToDLL, (PVOID)argv[1], MAX_PATH);
		memcpy((PVOID)remoteProcessName, (PVOID)argv[2], MAX_PATH);
	}
	else
	{
		wprintf(L"Type full(!) path to dll: ");
		wscanf_s(L"%s", pathToDLL, MAX_PATH + 1);
		wprintf(L"Type name of process: ");
		wscanf_s(L"%s", remoteProcessName, MAX_PATH + 1);
	}

	wprintf(L"========================================\n");
	wprintf(L"Path to dll: '%s'\n", pathToDLL);
	wprintf(L"Process to inject: '%s'\n", remoteProcessName);
	wprintf(L"========================================\n");
}



DWORD GetProcessIDByName(const PWCHAR processName)
{
	assert(processName);

	HANDLE hProcessSnap = NULL;
	HANDLE hProcess = NULL;
	PROCESSENTRY32 pe32 = {};
	DWORD dwPriorityClass = 0;

	// Take a snapshot of all processes in the system.
	hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hProcessSnap == INVALID_HANDLE_VALUE)
	{
		printError(TEXT("CreateToolhelp32Snapshot (of processes)"));
		return 0;
	}

	// Set the size of the structure before using it.
	pe32.dwSize = sizeof(PROCESSENTRY32);

	// Retrieve information about the first process,
	// and exit if unsuccessful
	if (!Process32First(hProcessSnap, &pe32))
	{
		printError(TEXT("Process32First")); // show cause of failure
		CloseHandle(hProcessSnap);          // clean the snapshot object
		return 0;
	}

	// Now walk the snapshot of processes, and
	// display information about each process in turn
	do
	{
		if (wcscmp(pe32.szExeFile, processName) == 0)
		{
			CloseHandle(hProcessSnap);
			return pe32.th32ProcessID;
		}
	} while (Process32Next(hProcessSnap, &pe32));

	CloseHandle(hProcessSnap);
	return 0;
}



LPVOID WritePathToDLLToRemoteProcess(
	HANDLE remoteProcessHandler,
	const PWCHAR pathToDLL
)
{
	assert(remoteProcessHandler);
	assert(pathToDLL);

	const SIZE_T pathToDLLSizeInBytes = sizeof(pathToDLL[0]) * wcslen(pathToDLL);

	LPVOID pathToDLLRemoteAddress = VirtualAllocEx(
		remoteProcessHandler,
		NULL,
		pathToDLLSizeInBytes,
		MEM_RESERVE | MEM_COMMIT,
		PAGE_EXECUTE_READWRITE
	);
	if (pathToDLLRemoteAddress == NULL)
	{
		printError(TEXT("VirtualAllocEx"));
		ExitProgram(1);
	}

	SIZE_T numberOfBytesWritten = 0;
	BOOL retValue = WriteProcessMemory(
		remoteProcessHandler,
		pathToDLLRemoteAddress,
		(LPCVOID)pathToDLL,
		pathToDLLSizeInBytes,
		&numberOfBytesWritten
	);
	if (retValue == 0 || numberOfBytesWritten != pathToDLLSizeInBytes)
	{
		printError(TEXT("WriteProcessMemory"));
		ExitProgram(1);
	}

	return pathToDLLRemoteAddress;
}



void LoadDLLToRemoteProcess(
	HANDLE remoteProcessHandle,
	LPVOID pathToDLLRemoteAddress
)
{
	assert(remoteProcessHandle);
	assert(pathToDLLRemoteAddress);

	LPVOID loadLibraryAddress = (LPVOID)GetProcAddress(
		GetModuleHandle(L"kernel32.dll"),
		"LoadLibraryW"
	);
	if (loadLibraryAddress == NULL)
	{
		printError(TEXT("GetProcAddress"));
		ExitProgram(1);
	}

	HANDLE newThreadHandle = CreateRemoteThread(
		remoteProcessHandle,
		NULL,
		0,
		(LPTHREAD_START_ROUTINE)loadLibraryAddress,
		pathToDLLRemoteAddress,
		CREATE_SUSPENDED,
		NULL
	);
	if (newThreadHandle == NULL)
	{
		printError(TEXT("CreateRemoteThread"));
		ExitProgram(1);
	}

	Sleep(1000);

	if (ResumeThread(newThreadHandle) == (DWORD)-1)
	{
		printError(TEXT("ResumeThread"));
		ExitProgram(1);
	}
}



void printError(TCHAR* msg)
{
	DWORD eNum;
	TCHAR sysMsg[256];
	TCHAR* p;

	eNum = GetLastError();
	FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL, eNum,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
		sysMsg, 256, NULL);

	// Trim the end of the line and terminate it with a null
	p = sysMsg;
	while ((*p > 31) || (*p == 9))
		++p;
	do { *p-- = 0; } while ((p >= sysMsg) &&
		((*p == '.') || (*p < 33)));

	// Display the message
	_tprintf(TEXT("\n  WARNING: %s failed with error %d (%s)"), msg, eNum, sysMsg);
}



void ExitProgram(const int errorCode)
{
	system("pause");
	ExitProcess(errorCode);
}

