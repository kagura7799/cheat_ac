#pragma once

#include <Windows.h>
#include <map>
#include <string>
#include <TlHelp32.h>
#include <vector>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#include "../include/offsets.hpp" 
#include "../include/esp/esp.hpp"

class Memory {
private:
    DWORD pid;
    HWND hwnd;
    HANDLE hProcess;
    DWORD playerBase;
    DWORD baseAddress;

    const std::map<std::string, DWORD>* weaponOffsets;
    const std::map<std::string, DWORD>* miscellaneousOffsets; 

    uintptr_t getModuleBaseAddress(DWORD pid, const std::wstring& moduleName);

    int Players;

	float viewmatrix[16];
    DWORD entityTemp;
    DWORD entityPlayer; 
    int enemyHealth;
    char enemyName[20];
        
public:
    Memory();

    void setPlayerAmmo(int value);
    void setPlayerHp(int value);
    void setPlayerArmor(int value);
    void setGravity(bool value); 
    void setRecoil();
    void setWallHack(bool active);
};