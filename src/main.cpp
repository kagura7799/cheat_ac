#include <iostream>
#include <string>
#include <Windows.h>
#include <map>
#include <thread>
#include <atomic>

#include "../include/cheat.hpp"

#pragma comment(lib, "Gdi32.lib")

const std::string reset = "\033[0m";         
const std::string black = "\033[30m";        
const std::string red = "\033[31m";          
const std::string green = "\033[32m";        
const std::string yellow = "\033[33m";       
const std::string blue = "\033[34m";         
const std::string purple = "\033[35m";       
const std::string cyan = "\033[36m";         
const std::string white = "\033[37m";        

void SetCursorPosition(int x, int y) {
    COORD coord = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

std::atomic<bool> godModeActive(false);
std::atomic<bool> gravityActive(false);
std::atomic<bool> recoilActive(false);
std::atomic<bool> vallHackActive(false);

std::map<std::string, bool> cheatTypes {
    {"GodMode", true},          
    {"Disable Gravity", true},  
    {"Disable Recoil", true},  
    {"VallHack", true},  
};

std::map<std::string, bool> cheatStatus {
    {"GodMode", false},
    {"Disable Gravity", false},
    {"Disable Recoil", false},
    {"VallHack", false},  
};

void drawMenu() {
    SetCursorPosition(0, 4);
    std::cout << red << "========= ASSAULT CUBE CHEAT =========" << reset << std::endl;
    std::cout << "(by \"414 kagura\")" << std::endl;
    std::cout << "\n";
    std::cout << "DISABLE GRAVITY - F1" << std::endl;
    std::cout << "DISABLE RECOIL - F2" << std::endl;
    std::cout << "GOD MODE - F3" << std::endl;
    std::cout << "VALLHACK - F4" << std::endl;
    std::cout << std::endl;

    for (const auto& [cheat, status] : cheatStatus) {
        std::cout << red << std::endl;
        std::cout << "------------------------------" << std::endl;
        std::cout << (status ? "[+]" : "[]") << " " << cheat << std::endl;
        std::cout << "------------------------------" << std::endl;
        std::cout << reset << std::endl;
    }
}

void godModeLoop(Cheat& cheat) {
    while (godModeActive) {
        cheat.godMode(414, 414, 414);
        Sleep(100);
    }

    cheat.godMode(100, 0, 30);
}

void gravityLoop(Cheat& cheat) {
    while (gravityActive) {
        cheat.setGravity(true);
        Sleep(100);
    }

    cheat.setGravity(false);
}

void recoilLoop(Cheat& cheat) {
    while (recoilActive) {
        cheat.setRecoil();
        Sleep(100);
    }
}

void vallHackLoop(Cheat& cheat) {
    while (vallHackActive) {
        cheat.setVallHack(true);
        Sleep(5);
    }

    cheat.setVallHack(false);
}

void handleKeyPresses(Cheat& cheat) {
    system("cls");

    while (true) {
        drawMenu();

        if (GetAsyncKeyState(VK_F1) & 0x8000) {
            cheatStatus["Disable Gravity"] = !cheatStatus["Disable Gravity"];

            if (cheatStatus["Disable Gravity"]) {
                gravityActive = true;
                std::thread(gravityLoop, std::ref(cheat)).detach();
            } else {
                gravityActive = false;
            }
        }

        if (GetAsyncKeyState(VK_F2) & 0x8000) {
            cheatStatus["Disable Recoil"] = !cheatStatus["Disable Recoil"];

            if (cheatStatus["Disable Recoil"]) {
                recoilActive = true;
                std::thread(recoilLoop, std::ref(cheat)).detach();
            } else {
                recoilActive = false;
            }
        }

        if (GetAsyncKeyState(VK_F3) & 0x8000) {
            cheatStatus["GodMode"] = !cheatStatus["GodMode"];

            if (cheatStatus["GodMode"]) {
                godModeActive = true;
                std::thread(godModeLoop, std::ref(cheat)).detach();
            } else {
                godModeActive = false;
            }
        }

        if (GetAsyncKeyState(VK_F4) & 0x8000) {
            cheatStatus["VallHack"] = !cheatStatus["VallHack"];
            if (cheatStatus["VallHack"]) {
                vallHackActive = true;
                std::thread(vallHackLoop, std::ref(cheat)).detach();
            } else {
                vallHackActive = false;
            }
        }

        Sleep(100);
    }
}

int main() {
    Cheat cheat;
    handleKeyPresses(cheat);
    return 0;
}
