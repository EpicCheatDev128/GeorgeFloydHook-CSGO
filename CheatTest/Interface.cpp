#pragma once
#include "Interface.h"
#define sig_glow_manager "0F 11 05 ? ? ? ? 83 C8 01 C7 05 ? ? ? ? 00 00 00 00"
void Interfaces::InitInterface() {
	pDevice = **(DWORD**)(FindPattern("shaderapidx9.dll", "A1 ?? ?? ?? ?? 50 8B 08 FF 51 0C") + 0x1);
	pEntityList = GetInterface<ClientEntityList, interface_type::index>("client.dll", "VClientEntityList003");
	pClient = GetInterface<iBaseClient, interface_type::index>("client.dll", "VClient018");
	pClientMode = **reinterpret_cast<i_client_mode***>((*reinterpret_cast<uintptr_t**>(pClient))[10] + 5);
	pModelInfo = GetInterface<ModelInfo, interface_type::index>("engine.dll", "VModelInfoClient004");
	pConsole = GetInterface<i_console, interface_type::index>("vstdlib.dll", "VEngineCvar007");
	pEngine = GetInterface<iv_engine_client, interface_type::index>("engine.dll", "VEngineClient014");
	pGlobals = **reinterpret_cast<c_global_vars_base***>((*reinterpret_cast<uintptr_t**>(pClient))[11] + 10);
	pModelRender = GetInterface<iv_model_render, interface_type::index>("engine.dll", "VEngineModel016");
	pMaterialSystem = GetInterface<i_material_system, interface_type::index>("materialsystem.dll", "VMaterialSystem080");
	pGlowManager = reinterpret_cast<glow_manager_t*>(*reinterpret_cast<uintptr_t*>(FindPattern("client.dll", sig_glow_manager) + 3));
	pClientState = **reinterpret_cast<i_client_state***>(FindPattern("engine.dll", "A1 ? ? ? ? 8B 80 ? ? ? ? C3") + 1);
}