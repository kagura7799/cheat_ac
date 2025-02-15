#include <iostream>
#include <string>
#include <Windows.h>
#include <map>
#include <thread>
#include <atomic>

#include "../include/cheat.hpp"

void SetCursorPosition(int x, int y) {
    COORD coord = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

std::atomic<bool> godModeActive(false);
std::atomic<bool> gravityActive(false);

std::map<std::string, bool> cheatTypes {
    {"GodMode", true},          
    {"Disable Gravity", true},  
};

std::map<std::string, bool> cheatStatus {
    {"GodMode", false},
    {"Disable Gravity", false},
};

void drawMenu() {
    SetCursorPosition(0, 4);
    std::cout << "========= ASSAULT CUBE CHEAT =========" << std::endl;
    std::cout << "(by \"414 kagura\")" << std::endl;
    std::cout << "[!] Exit - ESC " << std::endl;
    std::cout << "DISABLE GRAVITY - ALT + F1" << std::endl;
    std::cout << "GOD MODE - ALT + F2" << std::endl;
    std::cout << std::endl;

    for (const auto& [cheat, status] : cheatStatus) {
        std::cout << "------------------------------" << std::endl;
        std::cout << (status ? "[+]" : "[]") << " " << cheat << std::endl;
        std::cout << "------------------------------" << std::endl;
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

void handleKeyPresses(Cheat& cheat) {
    system("cls");

    while (true) {
        drawMenu();

        if ((GetAsyncKeyState(VK_MENU) & 0x8000) && (GetAsyncKeyState(VK_F1) & 0x8000)) {
            cheatStatus["Disable Gravity"] = !cheatStatus["Disable Gravity"];

            if (cheatStatus["Disable Gravity"]) {
                gravityActive = true;
                std::thread(gravityLoop, std::ref(cheat)).detach();
            } else {
                gravityActive = false;
            }
        }

        if ((GetAsyncKeyState(VK_MENU) & 0x8000) && (GetAsyncKeyState(VK_F2) & 0x8000)) {
            cheatStatus["GodMode"] = !cheatStatus["GodMode"];

            if (cheatStatus["GodMode"]) {
                godModeActive = true;
                std::thread(godModeLoop, std::ref(cheat)).detach();
            } else {
                godModeActive = false;
            }
        }

        if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
            godModeActive = false;
            gravityActive = false;
            break;
        }

        Sleep(100);
    }
}

int main() {
    Cheat cheat;
    handleKeyPresses(cheat);
    return 0;
}
