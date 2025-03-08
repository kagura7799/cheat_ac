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
#include "../include/aim/aimbot.hpp"

#define M_PI 3.14159265358979323846

struct Entity
{
    int hp;
    Vec3 enemyB;
    Vec3 enemyH;
};

class Memory
{
private:
    DWORD pid;
    HWND hwnd;
    HANDLE hProcess;
    DWORD playerBase;
    DWORD baseAddress;

    const std::map<std::string, DWORD> *weaponOffsets;
    const std::map<std::string, DWORD> *miscellaneousOffsets;

    uintptr_t getModuleBaseAddress(DWORD pid, const std::wstring &moduleName);
    void setEntityCoords(DWORD entity, Vec3& head, Vec3& body);
    void setEntityProperties(DWORD entityAddress);

    int countOfPlayers;

    float viewmatrix[16];

    DWORD entityPtr;
    DWORD entityEnemy;
    
    int enemyHealth;
    char enemyName[20];

public:
    Memory();

    Entity g_entity;

    void setPlayerAmmo(int value);
    void setPlayerHp(int value);
    void setPlayerArmor(int value);
    void setGravity(bool value);
    void setRecoil();
    void setWallHack(bool active);
    void setAimBot(bool active);
};