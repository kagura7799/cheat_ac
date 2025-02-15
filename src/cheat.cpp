#include "../include/cheat.hpp"

void Cheat::godMode(int hp, int armor, int ammo) {
    memory.setPlayerAmmo(ammo);
    memory.setPlayerHp(hp);    
    memory.setPlayerArmor(armor);    
}    

void Cheat::setGravity(bool value) {
    memory.setGravity(value);
}