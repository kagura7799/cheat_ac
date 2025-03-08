#include "../include/cheat.hpp"

void Cheat::godMode(int hp, int armor, int ammo)
{
    memory.setPlayerAmmo(ammo);
    memory.setPlayerHp(hp);
    memory.setPlayerArmor(armor);
}

void Cheat::setGravity(bool active)
{
    memory.setGravity(active);
}

void Cheat::setRecoil()
{
    memory.setRecoil();
}

void Cheat::setWallHack(bool active)
{
    memory.setWallHack(active);
}

void Cheat::setAimBot(bool active)
{
    memory.setAimBot(active);
}
