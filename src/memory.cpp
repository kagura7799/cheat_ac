#include "../include/memory.hpp"

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

    if (!GetWindowThreadProcessId(hwnd, &pid)) {
        std::cerr << "[ERROR] Assault Cube not found" << std::endl;;
        ExitProcess(1);
    }
    
    hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
    if (hProcess != NULL) {
        std::cout << "Process opened" << std::endl;
    }

    baseAddress = (DWORD)getModuleBaseAddress(pid, L"ac_client.exe");

    ReadProcessMemory(hProcess, (LPCVOID)(baseAddress + 0x195404), &playerBase, sizeof(DWORD), NULL);

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

void Memory::setRecoil() {
    uintptr_t INST_CHANGE_VIEWY = 0xC2EC3;
    std::vector<uint8_t> nopBytes = {0x90, 0x90, 0x90, 0x90, 0x90};

    WriteProcessMemory(hProcess, (LPVOID)(baseAddress + INST_CHANGE_VIEWY), nopBytes.data(), nopBytes.size(), NULL);
}

void Memory::setWallHack(bool active) {
    ESP esp(hProcess, (uintptr_t)baseAddress + basicOffsets["NumOfPlayers"], Players);

    if (active) {
        for (int i = 1; i < Players; i++) { 
            ReadProcessMemory(hProcess, (LPCVOID)(baseAddress + basicOffsets["ViewMatrix"]), &viewmatrix, sizeof(viewmatrix), NULL);

            ReadProcessMemory(hProcess, (LPCVOID)(baseAddress + basicOffsets["Entity"]), &entityTemp, sizeof(DWORD), NULL); 
            ReadProcessMemory(hProcess, (LPCVOID)(entityTemp + i * 4), &entityPlayer, sizeof(DWORD), NULL);
    
            ReadProcessMemory(hProcess, (LPCVOID)(entityPlayer + 0x205), &enemyName, 20, NULL);
            ReadProcessMemory(hProcess, (LPCVOID)(entityPlayer + 0xEC), &enemyHealth, 4, NULL);

            if (enemyHealth < 0) {
                continue;
            }

            ReadProcessMemory(hProcess, (LPCVOID)(entityPlayer + playerOffsets["axis"]["posx"]), &enemyB.x, sizeof(float), NULL);
            ReadProcessMemory(hProcess, (LPCVOID)(entityPlayer + playerOffsets["axis"]["posy"]), &enemyB.y, sizeof(float), NULL);
            ReadProcessMemory(hProcess, (LPCVOID)(entityPlayer + playerOffsets["axis"]["posz"]), &enemyB.z, sizeof(float), NULL);
            ReadProcessMemory(hProcess, (LPCVOID)(entityPlayer + playerOffsets["axis"]["headx"]), &enemyH.x, sizeof(float), NULL);
            ReadProcessMemory(hProcess, (LPCVOID)(entityPlayer + playerOffsets["axis"]["heady"]), &enemyH.y, sizeof(float), NULL);
            ReadProcessMemory(hProcess, (LPCVOID)(entityPlayer + playerOffsets["axis"]["headz"]), &enemyH.z, sizeof(float), NULL);

            esp.WallHack(enemyB, enemyH, viewmatrix, enemyName, enemyHealth);
        }
    }
}