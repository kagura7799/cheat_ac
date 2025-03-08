#include "../../include/esp/esp.hpp"

ESP::ESP(HANDLE hProcess, uintptr_t playerNumbers, int &Players)
{
	ReadProcessMemory(hProcess, (LPCVOID)playerNumbers, &Players, sizeof(Players), NULL);
}

std::wstring ESP::ConvertToWString(const char *str)
{
	int len = MultiByteToWideChar(CP_ACP, 0, str, -1, NULL, 0);
	std::wstring wstr(len, L'\0');
	MultiByteToWideChar(CP_ACP, 0, str, -1, &wstr[0], len);
	return wstr;
}

bool ESP::WorldToScreen(Vec3 pos, Vec2 *screen, float matrix[16], int windowWidth, int windowHeight)
{
	Vec4 clipCoords;

	clipCoords.x = pos.x * matrix[0] + pos.y * matrix[4] + pos.z * matrix[8] + matrix[12];
	clipCoords.y = pos.x * matrix[1] + pos.y * matrix[5] + pos.z * matrix[9] + matrix[13];
	clipCoords.z = pos.x * matrix[2] + pos.y * matrix[6] + pos.z * matrix[10] + matrix[14];
	clipCoords.w = pos.x * matrix[3] + pos.y * matrix[7] + pos.z * matrix[11] + matrix[15];

	if (clipCoords.w < 0.1f)
		return 0;

	Vec3 NDC;

	NDC.x = clipCoords.x / clipCoords.w;
	NDC.y = clipCoords.y / clipCoords.w;
	NDC.z = clipCoords.z / clipCoords.w;

	screen->x = (windowWidth / 2 * NDC.x) + (NDC.x + windowWidth / 2);
	screen->y = -(windowHeight / 2 * NDC.y) + (NDC.y + windowHeight / 2);

	return 1;
}

void ESP::WallHack(Vec3 EnemyPosition, Vec3 enemyHeadPos, float Matrix[16], int enemyHealth)
{
	updateWindowSizeData();

	if (WorldToScreen(EnemyPosition, &screen, Matrix, screenwidth, screenheight))
	{
		if (WorldToScreen(enemyHeadPos, &Head, Matrix, screenwidth, screenheight))
		{
			float height = (Head.y - 55.0f) - screen.y;
			float width = height / 2.0f;

			std::wstring enemytextHealth = std::to_wstring(enemyHealth);
			DrawBorderBox(htdc, Color, screen.x - (width / 2), screen.y, width, height, 2, enemytextHealth.c_str());
		}
	}
}