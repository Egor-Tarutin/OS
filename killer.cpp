#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <process.h>
#include <tlhelp32.h>
#include <winbase.h>
#include <cstring>
#include <sstream>
#include <iostream>

void kill_proc_by_id(int id) {
    HANDLE hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPALL, 0);
    PROCESSENTRY32 pEntry;
    pEntry.dwSize = sizeof(pEntry);
    BOOL hRes = Process32First(hSnapShot, &pEntry);
    while (hRes) {
        if (pEntry.th32ProcessID == id) {
            HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, 0,
                                          (DWORD)pEntry.th32ProcessID);
            if (hProcess != nullptr) {
                TerminateProcess(hProcess, 9);
                CloseHandle(hProcess);
            }
        }
        hRes = Process32Next(hSnapShot, &pEntry);
    }
    CloseHandle(hSnapShot);
}

void kill_proc_by_name(const char* filename) {
    HANDLE hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPALL, 0);
    PROCESSENTRY32 pEntry;
    pEntry.dwSize = sizeof(pEntry);
    BOOL hRes = Process32First(hSnapShot, &pEntry);
    size_t cSize = strlen(filename) + 1;
    auto* wc = new wchar_t[cSize];
    mbstowcs(wc, filename, cSize);
    while (hRes) {
        if (std::wcscmp(reinterpret_cast<const wchar_t*>(pEntry.szExeFile), wc) == 0) {
            HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, 0, (DWORD)pEntry.th32ProcessID);
            if (hProcess != nullptr) {
                TerminateProcess(hProcess, 9);
                CloseHandle(hProcess);
            }
        }
        hRes = Process32Next(hSnapShot, &pEntry);
    }
    CloseHandle(hSnapShot);
}

int main(int argc, char* argv[]) {
    const CHAR* name = "PROC_TO_KILL";
    const DWORD buffSize = 65535;
    char buffer[buffSize];
    std::cout << "Mr.Salieri sends his regards\n";
    GetEnvironmentVariableA(name, buffer, buffSize);
    std::stringstream ss(buffer);
    while (ss.getline(reinterpret_cast<char*>(&buffer), buffSize, ','))
        kill_proc_by_name(buffer);

    if (argc < 3)
        return 0;

    if(strcmp(argv[1], "--id") == 0)
        kill_proc_by_id(atoi(argv[2]));
    if (strcmp(argv[1], "--name") == 0)
        kill_proc_by_name(argv[2]);
    return 0;
}