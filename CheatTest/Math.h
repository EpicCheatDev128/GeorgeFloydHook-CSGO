#pragma once

#ifndef MATH_H
#define MATH_H

#include <algorithm>
#include <iostream>
#include <vector>
#include "vector3d.hpp"

inline const int SCREEN_WIDTH = GetSystemMetrics(SM_CXSCREEN);
inline const int SCREEN_HEIGHT = GetSystemMetrics(SM_CYSCREEN);

inline const double g_pi = 3.14159265358979323846;
inline const double g_radPi = 180.0 / g_pi;

struct Color {
	BYTE r, g, b;
	Color(BYTE ar, BYTE ag, BYTE ab) {
		r = ar;
		g = ag;
		b = ab;
	}
};

inline vec3_t calcAngle(vec3_t& a, vec3_t& b) {
	vec3_t angles;
	vec3_t delta;
	delta.x = (a.x - b.x);
	delta.y = (a.y - b.y);
	delta.z = (a.z - b.z);

	double hyp = sqrt(delta.x * delta.x + delta.y * delta.y);
	angles.x = (float)(atanf(delta.z / hyp) * 57.295779513082f);
	angles.y = (float)(atanf(delta.y / delta.x) * 57.295779513082f);

	angles.z = 0.0f;
	if (delta.x >= 0.0) { angles.y += 180.0f; }
	return angles;
}

inline vec3_t AngleVector(vec3_t meme) {
	auto sy = sin(meme.y / 180.f * static_cast<float>(3.141592654f));
	auto cy = cos(meme.y / 180.f * static_cast<float>(3.141592654f));

	auto sp = sin(meme.x / 180.f * static_cast<float>(3.141592654f));
	auto cp = cos(meme.x / 180.f * static_cast<float>(3.141592654f));

	return vec3_t(cp * cy, cp * sy, -sp);
}

inline void TransformVector(vec3_t& a, matrix_t& b, vec3_t& out) {
	out.x = a.dot(b.mat_val[0]) + b.mat_val[0][3];
	out.y = a.dot(b.mat_val[1]) + b.mat_val[1][3];
	out.z = a.dot(b.mat_val[2]) + b.mat_val[2][3];
}

inline float GetFOV(const vec3_t& view_angle, const vec3_t& aim_angle)
{
	vec3_t delta = aim_angle - view_angle;
	delta.clamp();

	return sqrtf(powf(delta.x, 2.0f) + powf(delta.y, 2.0f));
}

inline float DistancePointToLine(vec3_t Point, vec3_t LineOrigin, vec3_t Dir)
{
	vec3_t PointDir = Point - LineOrigin;

	auto TempOffset = PointDir.dot(Dir) / (Dir.x * Dir.x + Dir.y * Dir.y + Dir.z * Dir.z);
	if (TempOffset < 0.000001f)
		return FLT_MAX;

	auto PerpendicularPoint = LineOrigin + (Dir * TempOffset);

	return vec3_t(Point - PerpendicularPoint).length();
}

inline struct ViewMatrix {
	float matrix[16];
}matrix;

struct BacktrackingData
{
	float m_flSimulationTime;
	vec3_t m_vecHitboxPosition;
};
inline BacktrackingData Data[64][12];

#endif // !MATH_H

