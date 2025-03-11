#include "../include/memory.hpp"

uintptr_t Memory::getModuleBaseAddress(DWORD pid, const std::wstring &moduleName)
{
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, pid);
    if (!hSnapshot)
    {
        std::cerr << "[ERROR] Failed to create modules snapshot (errno: " << GetLastError() << ")\n";
        ExitProcess(1);
    }

    MODULEENTRY32W moduleEntry{};
    moduleEntry.dwSize = sizeof(moduleEntry);

    if (Module32FirstW(hSnapshot, &moduleEntry))
    {
        do
        {
            if (moduleName == moduleEntry.szModule)
            {
                CloseHandle(hSnapshot);
                return reinterpret_cast<uintptr_t>(moduleEntry.modBaseAddr);
            }
        } while (Module32NextW(hSnapshot, &moduleEntry));
    }

    return NULL;
}

Memory::Memory()
{
    hwnd = FindWindowA(NULL, "AssaultCube");

    if (!GetWindowThreadProcessId(hwnd, &pid))
    {
        std::cerr << "[ERROR] Assault Cube not found" << std::endl;
        ExitProcess(1);
    }

    hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
    if (hProcess != NULL)
    {
        std::cout << "Process opened" << std::endl;
    }

    baseAddress = (DWORD)getModuleBaseAddress(pid, L"ac_client.exe");

    ReadProcessMemory(hProcess, (LPCVOID)(baseAddress + 0x195404), &playerBase, sizeof(DWORD), NULL);

    weaponOffsets = &entityOffsets["weapon"];
    miscellaneousOffsets = &entityOffsets["miscellaneous"];
}

void Memory::setPlayerAmmo(int value)
{
    for (const auto &offset : *weaponOffsets)
        WriteProcessMemory(hProcess, (LPVOID)(playerBase + offset.second), &value, sizeof(int), NULL);
}

void Memory::setPlayerHp(int value)
{
    WriteProcessMemory(hProcess, (LPVOID)(playerBase + miscellaneousOffsets->at("hp")), &value, sizeof(int), NULL);
}

void Memory::setPlayerArmor(int value)
{
    WriteProcessMemory(hProcess, (LPVOID)(playerBase + miscellaneousOffsets->at("armor")), &value, sizeof(int), NULL);
}

void Memory::setGravity(bool value)
{
    WriteProcessMemory(hProcess, (LPVOID)(playerBase + miscellaneousOffsets->at("is_onground")), &value, sizeof(bool), NULL);
}

void Memory::setRecoil()
{
    uintptr_t INST_CHANGE_VIEWY = 0xC2EC3;
    std::vector<uint8_t> nopBytes = {0x90, 0x90, 0x90, 0x90, 0x90};

    WriteProcessMemory(hProcess, (LPVOID)(baseAddress + INST_CHANGE_VIEWY), nopBytes.data(), nopBytes.size(), NULL);
}

void Memory::setEntityProperties(DWORD entityAddress)
{
    ReadProcessMemory(hProcess, (LPCVOID)(entityAddress + entityOffsets["miscellaneous"]["hp"]), &g_entity.hp, sizeof(int), NULL);
    ReadProcessMemory(hProcess, (LPCVOID)(entityAddress + entityOffsets["miscellaneous"]["team"]), &g_entity.team, sizeof(int), NULL);

    ReadProcessMemory(hProcess, (LPCVOID)(entityAddress + entityOffsets["axis"]["posx"]), &g_entity.bodyPos.x, sizeof(float), NULL);
    ReadProcessMemory(hProcess, (LPCVOID)(entityAddress + entityOffsets["axis"]["posy"]), &g_entity.bodyPos.y, sizeof(float), NULL);
    ReadProcessMemory(hProcess, (LPCVOID)(entityAddress + entityOffsets["axis"]["posz"]), &g_entity.bodyPos.z, sizeof(float), NULL);
    ReadProcessMemory(hProcess, (LPCVOID)(entityAddress + entityOffsets["axis"]["headx"]), &g_entity.headPos.x, sizeof(float), NULL);
    ReadProcessMemory(hProcess, (LPCVOID)(entityAddress + entityOffsets["axis"]["heady"]), &g_entity.headPos.y, sizeof(float), NULL);
    ReadProcessMemory(hProcess, (LPCVOID)(entityAddress + entityOffsets["axis"]["headz"]), &g_entity.headPos.z, sizeof(float), NULL);
}

void Memory::setWallHack(bool active)
{
    ESP esp(hProcess, (uintptr_t)baseAddress + basicOffsets["NumOfPlayers"], countOfPlayers);

    if (active)
    {
        for (int i = 1; i < countOfPlayers; i++)
        {
            ReadProcessMemory(hProcess, (LPCVOID)(baseAddress + basicOffsets["ViewMatrix"]), &viewmatrix, sizeof(viewmatrix), NULL);
            ReadProcessMemory(hProcess, (LPCVOID)(baseAddress + basicOffsets["Entity"]), &entityPtr, sizeof(DWORD), NULL);
            ReadProcessMemory(hProcess, (LPCVOID)(entityPtr + i * 0x4), &entityEnemy, sizeof(DWORD), NULL);

            setEntityProperties(entityEnemy);

            if (g_entity.hp < 0 || g_entity.team == g_player.team)
                continue;

            esp.WallHack(g_entity.bodyPos, g_entity.headPos, viewmatrix, g_entity.hp);
        }
    }
}

void Memory::setAimBot(bool active)
{
    if (active)
    {
        Angles currentViewAngles;

        ReadProcessMemory(hProcess, (LPCVOID)(playerBase + entityOffsets["axis"]["headx"]), &playerH.x, sizeof(float), NULL);
        ReadProcessMemory(hProcess, (LPCVOID)(playerBase + entityOffsets["axis"]["heady"]), &playerH.y, sizeof(float), NULL);
        ReadProcessMemory(hProcess, (LPCVOID)(playerBase + entityOffsets["axis"]["headz"]), &playerH.z, sizeof(float), NULL);

        for (int i = 1; i < countOfPlayers; i++)
        {
            ReadProcessMemory(hProcess, (LPCVOID)(playerBase + entityOffsets["miscellaneous"]["team"]), &g_player.team, sizeof(int), NULL);

            ReadProcessMemory(hProcess, (LPCVOID)(baseAddress + basicOffsets["Entity"]), &entityPtr, sizeof(DWORD), NULL);
            ReadProcessMemory(hProcess, (LPCVOID)(entityPtr + i * 0x4), &entityEnemy, sizeof(DWORD), NULL);

            setEntityProperties(entityEnemy);

            if (g_entity.hp < 0 || g_entity.team == g_player.team)
                continue;

            Angles targetAngles = CalcAngle(playerH, g_entity.headPos);

            WriteProcessMemory(hProcess, (LPVOID)(playerBase + entityOffsets["axis"]["viewx"]), &targetAngles.yaw, sizeof(float), NULL);
            WriteProcessMemory(hProcess, (LPVOID)(playerBase + entityOffsets["axis"]["viewy"]), &targetAngles.pitch, sizeof(float), NULL);
        }
    }
}