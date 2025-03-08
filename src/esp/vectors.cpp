#include "../../include/vectors.hpp"

Vec2 screen;
Vec2 Head;

Vec3 enemyB;
Vec3 enemyH;

Vec3 playerB;
Vec3 playerH;

HBRUSH Color = CreateSolidBrush(RGB(255, 255, 255));

HWND hwnd = FindWindowA(NULL, "AssaultCube");
HDC htdc = GetDC(hwnd);

RECT windowSize;

int screenwidth;
int screenheight;

void updateWindowSizeData() {
    GetWindowRect(hwnd, &windowSize);

    screenwidth = windowSize.right - windowSize.left;
    screenheight = windowSize.bottom - windowSize.top;
}