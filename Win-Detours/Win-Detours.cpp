// 'Win-Detours.cpp : This file contains the 'main' function. Program execution begins and ends there.
//'main' process that will take input from the user and call into sub-projects to outline functionality offered by Detours

// TODO: Make sub projects as dependencies for this project and include them in subdirectories

#include <iostream>
#include <Windows.h>


// Inject into an already running process and attempt to use our callbacks that way
BOOL handleInjectProcessDetours()
{


    return TRUE;
}


// Create a new instance of a binary via DetourCreateProcessWithDllEx()
BOOL handleNewProcessDetours()
{

    return TRUE;
}

// Modify an existing binary via DetourBinaryEditImports()
BOOL handleModifyBinaryDetours()
{

    return TRUE;
}

// Call into our pre-built DLL that will display the baseline for using these custom callbacks 
BOOL handleNativeDetours()
{


    return TRUE;
}

int main()
{
    std::cout << "Hello World!\n";
}


