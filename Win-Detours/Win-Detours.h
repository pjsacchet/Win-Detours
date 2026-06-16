#pragma once

#include <iostream>
#include <string>
#include <Windows.h>

typedef BOOL(__stdcall* DoNativeDetours)(); // exported from Detours-Native.dll
typedef BOOL(__stdcall* ModifyExistingBinary)(std::string inputFilePath, std::string outputFilePath); // exported from Detours-Modify-Binary.dll
typedef BOOL(__stdcall* DetoursNewProcess)(std::string targetBinary, std::string callbackDLL); // exported from Detours-New-Process.dll

enum DETOURS
{
	EXIT,
	NATIVE,
	MODIFY,
	INSTANCE,
	INJECT
};