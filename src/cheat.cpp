#include <Windows.h>
#include <TlHelp32.h>
#include <iostream>
#include <string>

#include "offsets.cpp"

class Cheat {
private:
    uintptr_t getModuleBaseAddress(DWORD pid, const std::wstring& moduleName) {
        HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, pid);

        if (!hSnapshot) {
            std::cerr << "[ERROR] Failed to create modules snapshot (errno: " << GetLastError() << ")\n";
            ExitProcess(1);
        }

        MODULEENTRY32W moduleEntry{};
        moduleEntry.dwSize = sizeof(moduleEntry);

        if (Module32FirstW(hSnapshot, &moduleEntry)) {
            do {
            if (moduleName == moduleEntry.szModule) {
                CloseHandle(hSnapshot);
                return reinterpret_cast<uintptr_t>(moduleEntry.modBaseAddr);
            }
            } while (Module32NextW(hSnapshot, &moduleEntry));
        }

        return NULL;
    }

public:
    DWORD pid;
    HWND hwnd;
    HANDLE hProcess;
    uintptr_t playerBase;
    uintptr_t baseAddress;

    const std::map<std::string, uintptr_t>* weaponOffsets; 
    const std::map<std::string, uintptr_t>* miscellaneousOffsets; 

    Cheat() {
        hwnd = FindWindowA(NULL, "AssaultCube"); 
        GetWindowThreadProcessId(hwnd, &pid);

        hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
        if (hProcess != NULL) {
            std::cout << "Process opened" << std::endl;
        }
        
        baseAddress = getModuleBaseAddress(pid, L"ac_client.exe");
        
        ReadProcessMemory(hProcess, (LPCVOID)(baseAddress + 0x195404), &playerBase, sizeof(uintptr_t), NULL);
        std::cout << std::hex << playerBase << std::endl;

        weaponOffsets = &playerOffsets["weapon"];
        miscellaneousOffsets = &playerOffsets["miscellaneous"];
    }

    void godMode() {
        int hp = 999999999, armor = 999999999, ammo = 999999999;

        for (const auto& offset : *weaponOffsets) {
            WriteProcessMemory(hProcess, (LPVOID)(playerBase + offset.second), &ammo, sizeof(int), NULL);
        }

        WriteProcessMemory(hProcess, (LPVOID)(playerBase + miscellaneousOffsets->at("hp")), &hp, sizeof(int), NULL);
        WriteProcessMemory(hProcess, (LPVOID)(playerBase + miscellaneousOffsets->at("armor")), &armor, sizeof(int), NULL);
    }    
};