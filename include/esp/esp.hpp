#pragma once

#include "../../include/esp/render.hpp"
#include "../../include/vectors.hpp"

class ESP
{
public:
	ESP(HANDLE hProcess, uintptr_t playerNumbers, int &Players);
	bool WorldToScreen(Vec3 pos, Vec2 *screen, float matrix[16], int windowWidth, int windowHeight);
	void WallHack(Vec3 EnemyPosition, Vec3 enemyHeadPos, float Matrix[16], int enemyHealth);

private:
	std::wstring ConvertToWString(const char *str);
};
