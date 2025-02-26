#pragma once

#include <Windows.h>
#include <iostream>
#include <string>

#include "../include/memory.hpp"

class Cheat {
public:
    Memory memory;

    void godMode(int hp, int armor, int ammo);
    void setGravity(bool active);
    void setRecoil();
    void setWallHack(bool active);
};
