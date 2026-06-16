#pragma once
#define WIN32_LEAN_AND_MEAN 

#include <Windows.h>
#include <iostream>

#include "detours.h"

BOOL WINAPI DetoursNewProcess(std::string targetBinary, std::string callbackDLL);