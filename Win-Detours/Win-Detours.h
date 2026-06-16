#pragma once

#include <iostream>
#include <string>
#include <Windows.h>

typedef BOOL(__stdcall* DoNativeDetours)(); // exported from Detours-Native.dll
typedef BOOL(__stdcall* ModifyExistingBinary)(std::string inputFilePath, std::string outputFilePath); // exported from Detours-Modify-Binary.dll

enum DETOURS
{
	EXIT,
	NATIVE,
	MODIFY,
	INSTANCE,
	INJECT
};