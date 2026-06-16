#pragma once
#define WIN32_LEAN_AND_MEAN 

#include <Windows.h>
#include <iostream>

#include "detours.h"

// Store a pointer to the true sleep function so we can call it from our callback 
static DWORD(WINAPI* TrueSleepEx)(DWORD dwMilliseconds, BOOL bAlertable) = SleepEx;

BOOL DoNativeDetours();
BOOL DoNativeDetoursCleanup();