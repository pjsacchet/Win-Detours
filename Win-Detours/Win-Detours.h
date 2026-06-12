#pragma once

#include <iostream>
#include <string>
#include <Windows.h>

enum DETOURS
{
	EXIT,
	NATIVE,
	MODIFY,
	INSTANCE,
	INJECT
};