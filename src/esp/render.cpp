#include <iostream>
#include "../../include/esp/render.hpp"

void DrawFilledRect(HDC htdc, int x, int y, int w, int h, HBRUSH color) {
    RECT rect = { x, y, x + w, y + h };
    FillRect(htdc, &rect, color);
}

void DrawBorderBox(HDC htdc, HBRUSH Color, int x, int y, int w, int h, int thickness, const wchar_t* text, const wchar_t* text2) {

	DrawFilledRect(htdc, x + 2, y, w - 2, thickness, Color);
	DrawFilledRect(htdc, x, y, thickness, h, Color); 
	DrawFilledRect(htdc, (x + w), y, thickness, h, Color);
	DrawFilledRect(htdc, x, y + h, w + thickness, thickness, Color);
	
	SetTextColor(htdc, RGB(255, 255, 255));
	SetBkMode(htdc, TRANSPARENT);
 
	RECT enemyN = { x, y + h, x + w, y };
	RECT enemyHealth = { x, y - 20, x + w, y };
 
	DrawTextW(htdc, text2, -1, &enemyHealth, DT_CENTER | DT_TOP | DT_SINGLELINE);
}