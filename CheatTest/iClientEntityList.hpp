#pragma once
#include <cstdint>

class ClientEntityList {
public:
	void* get_client_entity(int index) {
		using original_fn = void* (__thiscall*)(ClientEntityList*, int);
		return (*(original_fn**)this)[3](this, index);
	}
	void* get_client_entity_handle(uintptr_t handle) {
		using original_fn = void* (__thiscall*)(ClientEntityList*, uintptr_t);
		return (*(original_fn**)this)[4](this, handle);
	}
	int get_highest_index() {
		using original_fn = int(__thiscall*)(ClientEntityList*);
		return (*(original_fn**)this)[6](this);
	}
};