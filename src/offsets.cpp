#include "../include/offsets.hpp"

std::map<std::string, DWORD> basicOffsets = 
{
    {"Entity", 0x18AC04},
    {"NumOfPlayers", 0x18AC0C},
    {"ViewMatrix", 0x17DFD0},
    {"inst_change_viewy", 0xC2EC3},
};

std::map<std::string, std::map<std::string, DWORD>> entityOffsets = 
{
    //---------------------------#
    // Axis                      #
    //---------------------------#
    {"axis", {
        {"posx", 0x28},
        {"posy", 0x2C},
        {"posz", 0x30},
        {"headx", 0x4},
        {"heady", 0x8},
        {"headz", 0xc},
        {"viewx", 0x34},
        {"viewy", 0x38},
    }},
    //---------------------------#
    // Weapons                   #
    //---------------------------#
    {"weapon", {
        {"assaultrifle_ammo", 0x140},
        {"submachinegun_ammo", 0x138},
        {"sniperrifle_ammo", 0x13c},
        {"shotgun_ammo", 0x134},
        {"carbine_ammo", 0x130},
        {"glock_ammo", 0x12c},
    }},
    
    //---------------------------#
    // Miscellaneous             #
    //---------------------------#
    {"miscellaneous", {
        {"name", 0x205},
        {"hp", 0xec},
        {"armor", 0xF0},
        {"team", 0x30C},
        {"is_onground", 0x5d},
        {"is_shooting", 0x204},
    }},
};