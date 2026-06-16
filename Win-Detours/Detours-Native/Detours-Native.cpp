// Main functionality we'll export for our main exe to utilize 
	// Allows users to play around in their own enviornment/executable 
	// Loaded in Win-Detours.exe

#include "Detours-Native.h"


// Custom hook for the SleepEx API call
	// Will be called instead of Sleep everytime Sleep is invoked in the loaded process 
DWORD WINAPI CustomSleepEx(DWORD dwMilliseconds, BOOL bAlertable)
{
	DWORD status = NO_ERROR;

	printf("In custom sleep callback! Calling real sleep function...\n");

	status = TrueSleepEx(dwMilliseconds, bAlertable);

	return status;
}

// Setup for detours functionality
	// Register our hooks/callbacks for the desired API(s) we want to monitor
	// Also exported in case calling directly is desired
BOOL DoNativeDetours()
{
	DWORD status = ERROR_SUCCESS;

	printf("Setting up detour callbacks...\n");

	DetourRestoreAfterWith();

	DetourTransactionBegin();

	DetourUpdateThread(GetCurrentThread());

	DetourAttach(&(PVOID&)TrueSleepEx, CustomSleepEx);

	status = DetourTransactionCommit();
	if (FAILED(status))
	{
		printf("ERROR; Failed DetourTranscationCommit; error 0x%X\n", status);
		return FALSE;
	}

	return TRUE;
}

// Teardown for detours functionality
	// Remove our registered callbacks for the previously hooked APIs
	// Also exported in case calling directly is desired
BOOL DoNativeDetoursCleanup()
{
	DWORD status = ERROR_SUCCESS;

	printf("Removing registered callbacks...\n");

	DetourTransactionBegin();

	DetourUpdateThread(GetCurrentThread());

	DetourDetach(&(PVOID&)TrueSleepEx, CustomSleepEx);

	status = DetourTransactionCommit();
	if (FAILED(status))
	{
		printf("ERROR; Failed DetourTranscationCommit; error 0x%X\n", status);
		return FALSE;
	}

	return TRUE;
}

// Main DLL entry point
	// For all hooked funcitons, register our hooks upon being loaded into target process
	// When we are unloaded, remove these hooks so we don't break anything 
BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
		DoNativeDetours();
		break;
	case DLL_PROCESS_DETACH:
	case DLL_THREAD_DETACH:
		DoNativeDetoursCleanup();
		break;
	}

	return TRUE;
}