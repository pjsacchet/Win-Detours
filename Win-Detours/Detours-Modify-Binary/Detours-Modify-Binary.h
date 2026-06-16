#pragma once
#define WIN32_LEAN_AND_MEAN 

#include <Windows.h>
#include <iostream>

#include "detours.h"

// Used as a param to our callback 
typedef struct _CallbackContext 
{
	LPCSTR dllName;	// the name of the dll we want to inject 
	BOOL added;		// whether or not we already added this dll
} CallbackContext, *PCallbackContext;

BOOL WINAPI ModifyExistingBinary(std::string inputFilePath, std::string outputFilePath);