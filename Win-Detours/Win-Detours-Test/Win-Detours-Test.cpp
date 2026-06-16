// Just a test file that will call sleep
    // If we modify it correctly, it will call our hooked version of sleep instead

#include "Win-Detours-Test.h"

int main()
{
    printf("Sleeping for 5 seconds!\n");

    Sleep(5000);
    
    return 0;
}

