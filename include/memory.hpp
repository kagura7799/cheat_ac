#pragma once

#include <Windows.h>
#include <map>
#include <string>
#include <TlHelp32.h>

#include "../include/offsets.hpp" 

class Memory {
private:
    DWORD pid;
    HWND hwnd;
    HANDLE hProcess;
    uintptr_t playerBase;
    uintptr_t baseAddress;

    const std::map<std::string, uintptr_t>* weaponOffsets; 
    const std::map<std::string, uintptr_t>* miscellaneousOffsets; 

    uintptr_t getModuleBaseAddress(DWORD pid, const std::wstring& moduleName);
        
public:
    Memory();
    void setPlayerAmmo(int value);
    void setPlayerHp(int value);
    void setPlayerArmor(int value);
};