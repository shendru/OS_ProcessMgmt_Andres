#include <windows.h>
#include <stdio.h>

int main()
{
    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    DWORD myPID = GetCurrentProcessId();
    printf("Parent: My PID = %lu\n", myPID);

    char cmdLine[256];
    sprintf(cmdLine, "child_echo.exe %lu", myPID);

    if (!CreateProcess(
            NULL,
            cmdLine,
            NULL, NULL,
            FALSE,
            0,
            NULL, NULL,
            &si, &pi))
    {
        printf("CreateProcess failed (%d).\n", GetLastError());
        return 1;
    }

    printf("Parent: Child created with PID %lu\n", pi.dwProcessId);

    WaitForSingleObject(pi.hProcess, INFINITE);

    DWORD exitCode;
    GetExitCodeProcess(pi.hProcess, &exitCode);

    printf("Parent: Child exited with code %lu\n", exitCode);

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    return 0;
}
