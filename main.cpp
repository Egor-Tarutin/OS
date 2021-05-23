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











    /*STARTUPINFO si = { 0 };
    PROCESS_INFORMATION pi = { 0 };
    std::cout << name << " { " << buffer << "};" << '\n';
    std::cout << "Create processes mspaint and notepad. It's important code have absolute path for this processes." <<
              "C:\\WINDOWS\\system32..." << "\n";
    CreateProcessW(L"C:\\WINDOWS\\system32\\mspaint.exe",
            nullptr, nullptr, nullptr,
            FALSE, 0, nullptr, nullptr,
                   reinterpret_cast<LPSTARTUPINFOW>(&si), &pi);
    CreateProcess(reinterpret_cast<LPCSTR>(L"C:\\WINDOWS\\system32\\notepad.exe"), nullptr, nullptr,
            nullptr, FALSE, NULL, nullptr, nullptr, &si, &pi);
    std::cout << "delete notepad throw id " << pi.dwProcessId << '\n';
    std::string text = &R"(C:\Users\Egor\CLionProjects\os_killer\cmake-build-debug\os_killer.exe --id )" [ pi.dwProcessId];
    wchar_t tmp[200];
    mbstowcs(tmp, text.c_str(), text.length());

    CreateProcess(nullptr, reinterpret_cast<LPSTR>(tmp), nullptr, nullptr, FALSE, NULL, nullptr, nullptr, &si, &pi);
    WaitForSingleObject(pi.hProcess, INFINITE);
    CloseHandle(pi.hProcess);

    std::cout << "round 2" << '\n';
    std::cout << "Create processes mspaint and notepad " << "\n";
    CreateProcess(reinterpret_cast<LPCSTR>(L"C:\\WINDOWS\\system32\\mspaint.exe"), nullptr, nullptr, nullptr, FALSE, NULL, nullptr, nullptr, &si, &pi);
    CreateProcess(reinterpret_cast<LPCSTR>(L"C:\\WINDOWS\\system32\\notepad.exe"), nullptr, nullptr, nullptr, FALSE, NULL, nullptr, nullptr, &si, &pi);
    std::cout << "delete explorer.exe throw name" << '\n';

    text = R"(C:\Users\Egor\CLionProjects\os_killer\cmake-build-debug\os_killer.exe --name mspaint.exe)";
    mbstowcs(tmp, text.c_str(), text.length());

    CreateProcess(nullptr, reinterpret_cast<LPSTR>(tmp), nullptr, nullptr, FALSE, NULL, nullptr, nullptr, &si, &pi);
    WaitForSingleObject(pi.hProcess, INFINITE);
    CloseHandle(pi.hProcess);
    std::cout << "it's normal explorer.exe just reload. Explorer.exe win" << '\n';

    SetEnvironmentVariableA(name, nullptr);
    buffer[0] = '\0';
    GetEnvironmentVariableA(name, buffer, buffSize);
    std::cout << name << " { " << buffer << "};" << '\n';*/

    //system("pause");
}