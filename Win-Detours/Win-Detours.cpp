// Main 'binary' for detours functionality
    // Will load supplemental DLLs (users can modify/play around with if desired) for each different scenario one would use detours to add custom callbacks
    // Scenarios:
        // Detour own executable with defined callbacks to certain APIs
        // Modify the export table of a existing binary to use custom callbacks 
        // Launch a new instance of a binary with custom callbacks
        // Inject our detour'd functionality into an already running executable 

#include "Win-Detours.h"

typedef BOOL(__stdcall* DoNativeDetours)(); // exported from Detours-Native.dll


// Call into our pre-built DLL that will display the baseline for using these custom callbacks 
BOOL HandleNativeDetours()
{
    HMODULE detoursNativeLib;
    DoNativeDetours doNativeDetours;

    // This functionality is held in our Detours-Native DLL so load that 
        // This DLL is a dependency so the path should be fine.... its also relative
        // TODO: detours really only does x86 so assume user will provide x86 debug or handle all cases
    detoursNativeLib = LoadLibrary(L"Detours-Native.dll");
    if (detoursNativeLib == NULL)
    {
        printf("ERROR; Failed LoadLibrary; error 0x%X\n", GetLastError());
        return FALSE;
    }

    doNativeDetours = GetProcAddress(detoursNativeLib, "DoNativeDetours");
    if (doNativeDetours == NULL)
    {
        printf("ERROR; Failed GetProcAddressl error 0x%X\n", GetLastError());
        return FALSE;
    }

    if (!doNativeDetours())
    {
        printf("ERROR Failed DoNativeDetours\n");
        return FALSE;
    }

    if (!FreeLibrary(detoursNativeLib))
    {
        printf("ERROR; Failed FreeLibrary; error 0x%X\n", GetLastError());
        return FALSE;
    }

    return TRUE;
}

// Modify an existing binary via DetourBinaryEditImports()
BOOL HandleModifyBinaryDetours()
{

    return TRUE;
}

// Create a new instance of a binary via DetourCreateProcessWithDllEx()
BOOL HandleNewProcessDetours()
{

    return TRUE;
}

// Inject into an already running process and attempt to use our callbacks that way
BOOL HandleInjectProcessDetours()
{


    return TRUE;
}

// Print some help for the user 
void PrintHelp()
{
    printf("Please select one of the following to explore Detours capabilitites:\n");
    printf("\t0) Exit\n");
    printf("\t1) Call Detour'd functions inside own DLL\n");
    printf("\t2) Modify an existing binary to call detour'd functions\n");
    printf("\t3) Launch an instance of a executable with detour'd functions\n");
    printf("\t4) Inject into an existing process in an attempt to detour existing functionality\n");

    return;
}

int main()
{
    std::string choice;
    BOOL exit = FALSE;

    while (!exit)
    {
        PrintHelp();

        std::getline(std::cin, choice);

        switch (std::stoi(choice))
        {
        // Exit the program
        case EXIT:
            printf("Exiting...\n");
            exit = TRUE;
            break;
        // User wants to just use Detours contained within its own program
        case NATIVE:
            printf("Executing native Detours functionality...\n");
            if (!HandleNativeDetours())
            {
                printf("ERROR; Failed handleNativeDetours; exiting...\n");
                exit = TRUE;
                break;
            }
            else
            {
                printf("Successfully executed detours functionality\n");
                break;
            }
        case MODIFY:
            printf("Executing modification of external binary...\n");
            if (!HandleModifyBinaryDetours())
            {
                printf("ERROR; Failed handleModifyBinaryDetours; exiting...\n");
                exit = TRUE;
                break;
            }
            else
            {
                printf("Successfully modified external binary using detours\n");
                break;
            }
        case INSTANCE:
            printf("Executing a new instance of a executable with detour'd functionality...\n");
            if (!HandleNewProcessDetours())
            {
                printf("ERROR; Failed handleNewProcessDetours; exiting...\n");
                exit = TRUE;
                break;
            }
            else
            {
                printf("Successfully launched new instance of binary with overwritten detours functionality\n");
                break;
            }
        case INJECT:
            printf("Attemtping to inject detuor'd functionality into running process...\n");
            if (!HandleInjectProcessDetours())
            {
                printf("ERROR; Failed handleInjectProcessDetours; exiting...\n");
                exit = TRUE;
                break;
            }
            else
            {
                printf("Successfully injected into process with new detours functionality\n");
                break;
            }
        }
    }
    

    return 0;
}


