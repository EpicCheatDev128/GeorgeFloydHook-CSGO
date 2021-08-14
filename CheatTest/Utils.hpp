#pragma once
#include <cstdint>
#include "vector3d.hpp"
#include <iostream>
#include <Windows.h>
#include <vector>

namespace utilities {
	template< typename t >
	__forceinline static t call_virtual(void* name, int offset) {
		int* table = *(int**)name;
		int address = table[offset];
		return (t)(address);
	}
}