// DLL will serve to open a target process to inject detours DLL into 
#include "Detours-Inject.h"


BOOL DoDetoursInject(UINT32 pid, std::string detoursDLL)
{
	HANDLE hProc, hThread;
	void* mem;
	SIZE_T bytesWritten = 0;

	printf("Opening process %u for inject with DLL %s...", pid, detoursDLL.c_str());

	// Open process
	hProc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
	if (hProc == NULL)
	{
		printf("ERROR; Failed OpenProcess; error 0x%X\n", GetLastError());
		return FALSE;
	}

	// Allocate memory in target process to write our DLL
	mem = VirtualAllocEx(hProc, NULL, detoursDLL.length(), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
	if (mem == NULL)
	{
		printf("ERROR; Failed VirtualAllocEx; error 0x%X\n", GetLastError());
		return FALSE;
	}

	if (!WriteProcessMemory(hProc, mem, detoursDLL.c_str(), detoursDLL.length(), &bytesWritten))
	{
		printf("ERROR; Failed WriteProcessMemory; error 0x%x\n", GetLastError());
		return FALSE;
	}

	if (bytesWritten == 0)
	{
		printf("ERROR; Wrote 0 bytes to process memory!\n");
		return FALSE;
	}

	hThread = 



	return TRUE;
}