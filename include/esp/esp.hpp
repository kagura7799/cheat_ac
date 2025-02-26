#pragma once

#include "../../include/esp/render.hpp"
#include "../../include/esp/vectors.hpp"

class ESP {
public:
	ESP(HANDLE hProcess, uintptr_t playerNumbers, int& Players);
	bool WorldToScreen(Vec3 pos, Vec2* screen, float matrix[16], int windowWidth, int windowHeight);
	void WallHack(Vec3 EnemyPosition, Vec3 enemyHeadPos, float Matrix[16], char* enemyN, int enemyHealth);
	static float GetDistance3D(Vec3 m_pos, Vec3 en_pos);
    static float GetDistance2D(Vec3 m_pos, Vec3 en_pos);
    static Vec3 CalculateAngles(Vec3 m_pos, Vec3 en_pos);

private:
	std::wstring ConvertToWString(const char* str);
};
