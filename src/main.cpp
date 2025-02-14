#include <iostream>
#include <string>
#include <Windows.h>

#include "../include/cheat.hpp"

// for update console
void SetCursorPosition(int x, int y) {
    COORD coord = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

int main() {
    std::string godModeStatus = "[]";
    Cheat cheat;

    system("cls");

    while (true) {
        SetCursorPosition(0, 4);
        std::cout << "                              " << std::endl;
        SetCursorPosition(0, 4);

        std::cout << "========= ASSAULT CUBE CHEAT =========" << std::endl;
        std::cout << "(by \"414 kagura\")" << std::endl;
        std::cout << "[!] Exit - ESC " << std::endl;
        std::cout << std::endl;
        std::cout << "------------------------------" << std::endl;
        std::cout << godModeStatus << " GOD MODE (Alt + F1)" << std::endl;
        // std::cout << godModeStatus << " Disable gravity (Alt + F2)" << std::endl;
        // std::cout << godModeStatus << " Disable recoil (Alt + F3)" << std::endl;
        std::cout << "------------------------------" << std::endl;

        if ((GetAsyncKeyState(VK_MENU) & 0x8000) && (GetAsyncKeyState(VK_F1) & 0x8000)) {
            if (godModeStatus == "[+]") {
                godModeStatus = "[]";
                cheat.godMode(100, 0, 30);
            } 
                
            else {
                godModeStatus = "[+]";
                cheat.godMode(414999999, 414999999, 41499999);
            }
        }

        if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
            break;
        }

        Sleep(100);
    }

    return 0;
}
