#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <gdiplus.h>
#include <math.h>
#include <iostream>
#include <TlHelp32.h>
#include <sstream>

extern int screenwidth;
extern int screenheight;

typedef struct
{
	float x, y, z, w;
} Vec4;

struct Vec3
{
	float x, y, z;

	Vec3 operator-(const Vec3 &other) const
	{
		return {x - other.x, y - other.y, z - other.z};
	}
};

struct Angles
{
	float pitch, yaw;
};

typedef struct
{
	float x, y;
} Vec2;

extern Vec2 screen, Head;

extern Vec3 enemyB, enemyH;
extern Vec3 playerB, playerH;

extern HWND hwnd;
extern HDC htdc;
extern HBRUSH Color;

extern RECT windowSize;
extern BOOL getWindowSize;

void updateWindowSizeData();