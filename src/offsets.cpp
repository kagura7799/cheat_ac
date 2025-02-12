#include <map>
#include <string>

std::map<std::string, std::map<std::string, uintptr_t>> playerOffsets = {
    //---------------------------#
    // Axis                      #
    //---------------------------#
    {"axis", {
        {"posx", 0x2c},
        {"posy", 0x28},
        {"posz", 0x30},
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
        {"is_onground", 0x5d},
        {"is_shooting", 0x204},
    }},
};
