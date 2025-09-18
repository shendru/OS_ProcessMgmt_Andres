#include <windows.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    DWORD myPID = GetCurrentProcessId();

    if (argc < 2)
    {
        printf("Child: My PID = %lu | No parent PID received!\n", myPID);
        Sleep(20000);
        return 1;
    }

    DWORD parentPID = atoi(argv[1]);

    printf("Child: My PID = %lu | Parent PID = %lu\n", myPID, parentPID);

    Sleep(20000);

    return 0;
}
