#include "../../include/aim/aimbot.hpp"

float Math_Distance3D(Vec3 pos1, Vec3 pos2) 
{
    return sqrtf(powf(pos2.x - pos1.x, 2) + powf(pos2.y - pos1.y, 2) + powf(pos2.z - pos1.z, 2));
}

Angles CalcAngle(const Vec3 &source, const Vec3 &target)
{
    Angles angles;

    angles.yaw = -atan2f(target.x - source.x, target.y - source.y) / M_PI * 180.f + 180.f;
    angles.pitch = asinf((target.z - source.z) / Math_Distance3D(source, target)) * 180 / M_PI;

    return angles;
}