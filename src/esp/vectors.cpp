#include "../../include/esp/vectors.hpp"

int screenwidth = GetSystemMetrics(SM_CXSCREEN);
int screenheight = GetSystemMetrics(SM_CYSCREEN);

Vec2 screen;
Vec2 Head;
Vec3 enemyB;
Vec3 enemyH;

HBRUSH Color = CreateSolidBrush(RGB(255, 0, 0));
HDC htdc;

void setHWND(HWND hwnd) {
    htdc = GetDC(hwnd);
}