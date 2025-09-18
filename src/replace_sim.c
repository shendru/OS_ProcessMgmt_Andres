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
    printf("Parent: My PID = %lu. Spawning replacement process...\n", myPID);

    char cmdLine[] = "cmd /c dir";

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

    WaitForSingleObject(pi.hProcess, INFINITE);

    DWORD exitCode;
    GetExitCodeProcess(pi.hProcess, &exitCode);

    printf("Parent: Replacement process exited with code %lu.\n", exitCode);

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    return exitCode;
}
