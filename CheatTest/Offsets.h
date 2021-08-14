#pragma once

#ifndef OFFSET_H
#define OFFSET_H

#include <iostream>
#include <Windows.h>
#include "Entity.hpp"
#include "Math.h"


#define dwViewMatrix 0x4D94AD4 // зимаме този адрес от "hazedumper" защото незнам как да го намеря от "IDA 64"


#define FL_ONGROUND (1 << 0)

inline uintptr_t baseModule, engineModule;
inline player_t* localPlayer;

template <typename T> T ReadProcMem(uintptr_t Add) {
    return *(T*)Add;
}

template <typename T> void WriteProcMem(uintptr_t offset, T data) {
    *reinterpret_cast<T*>(offset) = data;
}

inline vec3_t WorldToScreen(const struct vec3_t pos) {
	vec3_t out;
	float _x = matrix.matrix[0] * pos.x + matrix.matrix[1] * pos.y + matrix.matrix[2] * pos.z + matrix.matrix[3];
	float _y = matrix.matrix[4] * pos.x + matrix.matrix[5] * pos.y + matrix.matrix[6] * pos.z + matrix.matrix[7];
	out.z = matrix.matrix[12] * pos.x + matrix.matrix[13] * pos.y + matrix.matrix[14] * pos.z + matrix.matrix[15];

	_x *= 1.f / out.z;
	_y *= 1.f / out.z;

	out.x = SCREEN_WIDTH * .5f;
	out.y = SCREEN_HEIGHT * .5f;

	out.x += 0.5f * _x * SCREEN_WIDTH + 0.5f;
	out.y -= 0.5f * _y * SCREEN_HEIGHT + 0.5f;

	return out;
}
#endif // !OFFSET_H

