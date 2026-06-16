// File will implement functionality for starting an instance of a target binary with a desired dll with detours implemented callbacks
#include "Detours-New-Process.h"


// Start an instance of a new process with imported DLL that implements callbacks
BOOL WINAPI DetoursNewProcess(std::string targetBinary, std::string callbackDLL)
{
	STARTUPINFOA startInfo = { 0 };
	PROCESS_INFORMATION processInfo = { 0 };

	startInfo.cb = sizeof(startInfo);

	if (!DetourCreateProcessWithDllExA(targetBinary.c_str(), NULL, NULL, NULL, FALSE, CREATE_DEFAULT_ERROR_MODE,
		NULL, NULL, &startInfo, &processInfo, callbackDLL.c_str(), NULL))
	{
		printf("ERROR; Failed DetourCreateProcessWithDllExA; error 0x%X\n", GetLastError());
		return FALSE;
	}

	printf("Successfully created injected process with PID %lu\n", processInfo.dwProcessId);

	// Wait for this process to finish
	WaitForSingleObject(processInfo.hProcess, INFINITE);

	CloseHandle(processInfo.hProcess);
	CloseHandle(processInfo.hThread);

	return TRUE;
}