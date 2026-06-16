// This DLL serves to implement detours functionality where we are given an executable and ant to inject our own callbacks into it
	// Very helpful for potentially malicious use of windwos APIs
#include "Detours-Modify-Binary.h"


// This callback will be called each time we encounter a import in the import table for target binary
	// Same pimitive as PF_DETOUR_BINARY_BYWAY_CALLBACK
BOOL WINAPI AddDllBywayCallback(PVOID pContext, LPCSTR file, LPCSTR* outFile)
{
	CallbackContext* context = (CallbackContext*)pContext;

	// If theres a empty spot inject our dll to be loaded	
		// Also check to see that we havent already written our DLL to this binary
	if (file == NULL) 
	{
		if (!context->added)
		{
			*outFile = context->dllName;
			context->added = TRUE;
			printf("Added DLL to import table!\n");
		}
		else
		{
			outFile = NULL;
		}		
	}

	// Otherwise just move to the next
	else
	{
		printf("Already added DLL to import table\n");
		*outFile = file;
	}

	return TRUE;
}

// Exported; will be called into to write new binary with modified import table
BOOL WINAPI ModifyExistingBinary(std::string inputFilePath, std::string outputFilePath)
{
	HANDLE inputFile, outputFile;
	PDETOUR_BINARY detBinary;
	CallbackContext context = { 0 };

	// Attempt to open file paths
	inputFile = CreateFileA(inputFilePath.c_str(), GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (inputFile == INVALID_HANDLE_VALUE)
	{
		printf("ERROR; Failed to open existing file (%s); error 0x%X\n", inputFilePath.c_str(), GetLastError());
		return FALSE;
	}

	detBinary = DetourBinaryOpen(inputFile);
	if (!detBinary)
	{
		printf("ERROR; Failed DetourBinaryOpen; error 0x%X\n", GetLastError());
		return FALSE;
	}

	// Setup our context
	context.dllName = "Detours-Native.dll";
	context.added = FALSE;

	// Edit imports
	if (!DetourBinaryEditImports(detBinary, &context, AddDllBywayCallback, NULL, NULL, NULL))
	{
		printf("ERROR; Failed DetourBinaryEditImports; error 0x%X\n", GetLastError());
		return FALSE;
	}

	// Now write to the new binary
	outputFile = CreateFileA(outputFilePath.c_str(), GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (outputFile == INVALID_HANDLE_VALUE)
	{
		printf("ERROR; Failed CreateFileA (create new file) (%s); error 0x%X\n", outputFilePath.c_str(), GetLastError());
		return FALSE;
	}

	if (!DetourBinaryWrite(detBinary, outputFile))
	{
		printf("ERROR; Failed DetourBinaryWrite; error 0x%X\n", GetLastError());
		return FALSE;
	}

	printf("Wrote to output file\n");

	// Cleanup
	DetourBinaryClose(detBinary);
	CloseHandle(inputFile);
	CloseHandle(outputFile);


	return TRUE;
}