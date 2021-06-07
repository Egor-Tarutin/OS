#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <windows.h>
#include <string>

int main() {
    const CHAR* name = "PROC_TO_KILL";
    const CHAR* value = "notepad.exe,SndVol.exe";
    const DWORD buffSize = 65535;
    char buffer[buffSize];
    SetEnvironmentVariableA(name, value);
    GetEnvironmentVariableA(name, buffer, buffSize);

    STARTUPINFO si_1 = {0};
    STARTUPINFO si_2 = {0};
    PROCESS_INFORMATION pi_1 = {0};
    PROCESS_INFORMATION pi_2 = {0};
    std::cout << "Buffer: " << buffer << '\n' << "Init 2 processes: \n";

    CreateProcess("C:\\Windows\\System32\\notepad.exe", NULL, NULL, NULL, false, 0, NULL, NULL, &si_1, &pi_1);
    CreateProcess("C:\\Windows\\System32\\SndVol.exe", NULL, NULL, NULL, false, 0, NULL, NULL, &si_2, &pi_2);
    std::cout << "ID of processes is: " << pi_1.dwProcessId << " " << pi_2.dwProcessId << '\n';

    system("pause");
}
