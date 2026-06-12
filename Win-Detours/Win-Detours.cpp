
#include "Win-Detours.h"


// Call into our pre-built DLL that will display the baseline for using these custom callbacks 
BOOL handleNativeDetours()
{
    // This functionality is held in our Detours-Native DLL so load that 

    return TRUE;
}

// Modify an existing binary via DetourBinaryEditImports()
BOOL handleModifyBinaryDetours()
{

    return TRUE;
}

// Create a new instance of a binary via DetourCreateProcessWithDllEx()
BOOL handleNewProcessDetours()
{

    return TRUE;
}

// Inject into an already running process and attempt to use our callbacks that way
BOOL handleInjectProcessDetours()
{


    return TRUE;
}

// Print some help for the user 
void printHelp()
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
        printHelp();

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
            if (!handleNativeDetours())
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
            if (!handleModifyBinaryDetours())
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
            if (!handleNewProcessDetours())
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
            if (!handleInjectProcessDetours())
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


