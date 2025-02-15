#include "../include/memory.hpp"
#include <iostream>

uintptr_t Memory::getModuleBaseAddress(DWORD pid, const std::wstring& moduleName) {
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

Memory::Memory() {
    hwnd = FindWindowA(NULL, "AssaultCube"); 
    GetWindowThreadProcessId(hwnd, &pid);

    hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
    if (hProcess != NULL) {
        std::cout << "Process opened" << std::endl;
    }
    
    baseAddress = getModuleBaseAddress(pid, L"ac_client.exe");
    ReadProcessMemory(hProcess, (LPCVOID)(baseAddress + 0x195404), &playerBase, sizeof(uintptr_t), NULL);

    weaponOffsets = &playerOffsets["weapon"];
    miscellaneousOffsets = &playerOffsets["miscellaneous"];
}

void Memory::setPlayerAmmo(int value) {
    for (const auto& offset : *weaponOffsets)
        WriteProcessMemory(hProcess, (LPVOID)(playerBase + offset.second), &value, sizeof(int), NULL);
}

void Memory::setPlayerHp(int value) {
    WriteProcessMemory(hProcess, (LPVOID)(playerBase + miscellaneousOffsets->at("hp")), &value, sizeof(int), NULL);
}

void Memory::setPlayerArmor(int value) {
    WriteProcessMemory(hProcess, (LPVOID)(playerBase + miscellaneousOffsets->at("armor")), &value, sizeof(int), NULL);
}

void Memory::setGravity(bool value) {
    WriteProcessMemory(hProcess, (LPVOID)(playerBase + miscellaneousOffsets->at("is_onground")), &value, sizeof(bool), NULL);
}

void Memory::setRecoil(bool enable) {
    uintptr_t INST_CHANGE_VIEWY = 0xC2EC3;
    std::vector<uint8_t> nopBytes = {0x90, 0x90, 0x90, 0x90, 0x90};

    WriteProcessMemory(hProcess, (LPVOID)(0x400000 + INST_CHANGE_VIEWY), nopBytes.data(), nopBytes.size(), NULL);
}