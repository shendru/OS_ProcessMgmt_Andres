#include <windows.h>
#include <stdio.h>

int main()
{
    STARTUPINFO si1, si2;
    PROCESS_INFORMATION pi1, pi2;

    ZeroMemory(&si1, sizeof(si1));
    si1.cb = sizeof(si1);
    ZeroMemory(&pi1, sizeof(pi1));

    ZeroMemory(&si2, sizeof(si2));
    si2.cb = sizeof(si2);
    ZeroMemory(&pi2, sizeof(pi2));

    DWORD myPID = GetCurrentProcessId();
    printf("Parent: My PID = %lu\n", myPID);

    char cmdLine1[256];
    char cmdLine2[256];
    sprintf(cmdLine1, "child_echo.exe %lu", myPID);
    sprintf(cmdLine2, "child_echo.exe %lu", myPID);

    if (!CreateProcess(
            NULL, cmdLine1,
            NULL, NULL, FALSE, 0,
            NULL, NULL, &si1, &pi1))
    {
        printf("CreateProcess (child 1) failed (%d).\n", GetLastError());
        return 1;
    }

    printf("Parent: First child created with PID %lu\n", pi1.dwProcessId);

    if (!CreateProcess(
            NULL, cmdLine2,
            NULL, NULL, FALSE, 0,
            NULL, NULL, &si2, &pi2))
    {
        printf("CreateProcess (child 2) failed (%d).\n", GetLastError());
        return 1;
    }

    printf("Parent: Second child created with PID %lu\n", pi2.dwProcessId);

    HANDLE processes[2] = {pi1.hProcess, pi2.hProcess};

    printf("Parent: Waiting for both children to finish...\n");

    WaitForMultipleObjects(2, processes, TRUE, INFINITE);

    DWORD exitCode1, exitCode2;
    GetExitCodeProcess(pi1.hProcess, &exitCode1);
    GetExitCodeProcess(pi2.hProcess, &exitCode2);

    printf("Parent: Child 1 (PID %lu) exited with code %lu\n", pi1.dwProcessId, exitCode1);
    printf("Parent: Child 2 (PID %lu) exited with code %lu\n", pi2.dwProcessId, exitCode2);

    CloseHandle(pi1.hProcess);
    CloseHandle(pi1.hThread);
    CloseHandle(pi2.hProcess);
    CloseHandle(pi2.hThread);

    return 0;
}
