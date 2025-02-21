#include <Windows.h>
#include <tlhelp32.h>
#include <iostream>
#include <string>
#include <vector>
#include <cstdio>

using namespace std;

// 版本信息
const string VERSION = "1.0";
const string WINDOW_TITLE = "EndField FPS Unlocker v" + VERSION;

// 全局配置
string process_name;
int target_fps = 30;

// 函数声明
DWORD GetPID(const string& processName);
uintptr_t GetModuleBase(DWORD pid, const string& moduleName);
bool WriteMemory(HANDLE hProcess, uintptr_t address, int value);
void SetConsoleTitle();

template<typename... Args>
string FormatString(const string& format, Args... args) {
    char buffer[1024];
    sprintf(buffer, format.c_str(), args...);
    return string(buffer);
}

DWORD GetPID(const string& processName) {
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (snapshot == INVALID_HANDLE_VALUE) return 0;

    PROCESSENTRY32 pe;
    pe.dwSize = sizeof(PROCESSENTRY32);

    if (!Process32First(snapshot, &pe)) {
        CloseHandle(snapshot);
        return 0;
    }

    do {
        if (processName.compare(pe.szExeFile) == 0) {
            CloseHandle(snapshot);
            return pe.th32ProcessID;
        }
    } while (Process32Next(snapshot, &pe));

    CloseHandle(snapshot);
    return 0;
}

uintptr_t GetModuleBase(DWORD pid, const string& moduleName) {
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, pid);
    if (snapshot == INVALID_HANDLE_VALUE) return 0;

    MODULEENTRY32 me;
    me.dwSize = sizeof(MODULEENTRY32);

    if (!Module32First(snapshot, &me)) {
        CloseHandle(snapshot);
        return 0;
    }

    do {
        if (moduleName.compare(me.szModule) == 0) {
            CloseHandle(snapshot);
            return (uintptr_t)me.modBaseAddr;
        }
    } while (Module32Next(snapshot, &me));

    CloseHandle(snapshot);
    return 0;
}

bool WriteMemory(HANDLE hProcess, uintptr_t address, int value) {
    SIZE_T bytesWritten;
    return WriteProcessMemory(hProcess, (LPVOID)address, &value, sizeof(value), &bytesWritten) 
        && bytesWritten == sizeof(value);
}

void SetConsoleTitle() {
    ::SetConsoleTitleA(WINDOW_TITLE.c_str());  // 使用 SetConsoleTitleA 来支持 char
}

void PrintUsage(const string& exe_name) {
    printf("Usage: %s -CN/-OS -fps <frame rate>\n", exe_name.c_str());
}

int main(int argc, char* argv[]) {
    // 设置控制台标题
    SetConsoleTitle();

    // 参数解析
    vector<string> args(argv, argv + argc);
    bool cn_specified = false, os_specified = false;

    for (size_t i = 1; i < args.size(); ++i) {
        if (args[i] == "-CN") {
            cn_specified = true;
            process_name = "Endfield_TBeta.exe";
        }
        else if (args[i] == "-OS") {
            os_specified = true;
            process_name = "Endfield_TBeta_OS.exe";
        }
        else if (args[i] == "-fps") {
            if (i + 1 < args.size()) {
                target_fps = atoi(args[++i].c_str());
            }
            else {
                cerr << "[-] Missing required arguments\n";
                return 1;
            }
        }
        else if (args[i] == "-v" || args[i] == "--version") {
            cout << WINDOW_TITLE << endl;
            return 0;
        }
    }

    // 验证参数
    if (!(cn_specified ^ os_specified) || target_fps <= 0) {
        PrintUsage(args[0]);
        cerr << "[-] Missing required arguments\n";
        return 1;
    }

    cout << "Endfield FPS Unlocker is running...\n";

    // 主循环
    const DWORD offset = 0x1B32E44;
    while (true) {
        DWORD pid = GetPID(process_name);
        if (pid == 0) {
            printf("[-] Process not found: %s\n", process_name.c_str());
            Sleep(2000);
            continue;
        }

        HANDLE hProcess = OpenProcess(
            PROCESS_VM_OPERATION | PROCESS_VM_WRITE | PROCESS_QUERY_INFORMATION,
            FALSE, pid
        );

        if (hProcess == NULL) {
            printf("[-] Error occurred: Unable to open process\n");
            Sleep(2000);
            continue;
        }

        uintptr_t base_addr = GetModuleBase(pid, "UnityPlayer.dll");
        if (base_addr == 0) {
            printf("[-] Error occurred: UnityPlayer.dll not found\n");
            CloseHandle(hProcess);
            Sleep(2000);
            continue;
        }

        uintptr_t target_addr = base_addr + offset;
        if (WriteMemory(hProcess, target_addr, target_fps)) {
            printf("[+] Successfully changed value at 0x%p to %d\n", (void*)target_addr, target_fps);
        }
        else {
            printf("[-] Error occurred: Failed to write memory\n");
        }

        CloseHandle(hProcess);
        Sleep(2000);
    }

    return 0;
}
