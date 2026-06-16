#pragma once

#include <iostream>
#include <string>
#include <Windows.h>

typedef BOOL(__stdcall* DoNativeDetours)(); // exported from Detours-Native.dll

enum DETOURS
{
	EXIT,
	NATIVE,
	MODIFY,
	INSTANCE,
	INJECT
};