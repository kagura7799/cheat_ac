#pragma once

#include <Windows.h>

void DrawBorderBox(HDC htdc, HBRUSH Color, int x, int y, int w, int h, int thickness, const wchar_t* text, const wchar_t* text2);
void DrawFilledRect(HDC htdc, int x, int y, int w, int h, HBRUSH color);

void getHWND();