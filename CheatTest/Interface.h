#pragma once
#ifndef INTERFACE_HPP
#define INTERFACE_HPP

#include <iostream>
#include "Patternscanning.h"
#include "iClientEntityList.hpp"
#include "IBaseClientDLL.hpp"
#include "ModelInfo.hpp"
#include "IConsole.hpp"
#include "IVEngineClient.hpp"
#include "GlobalVarsBase.hpp"
#include "ModelRender.hpp"
#include "GlowManager.hpp"
#include "iClientState.hpp"

namespace Interfaces {
	enum class interface_type { index, bruteforce };

	template <typename ret, interface_type type>
	ret* GetInterface(const std::string& module_name, const std::string& interface_name) {
		using create_interface_fn = void* (*)(const char*, int*);
		const auto fn = reinterpret_cast<create_interface_fn>(GetProcAddress(GetModuleHandle(module_name.c_str()), "CreateInterface"));

		if (fn) {
			void* result = nullptr;

			switch (type) {
			case interface_type::index:
				result = fn(interface_name.c_str(), nullptr);

				break;
			case interface_type::bruteforce:
				char buf[128];

				for (uint32_t i = 0; i <= 100; ++i) {
					memset(static_cast<void*>(buf), 0, sizeof buf);

					result = fn(interface_name.c_str(), nullptr);

					if (result)
						break;
				}

				break;
			}

			if (!result)
				throw std::runtime_error(interface_name + " wasn't found in " + module_name);

			return static_cast<ret*>(result);
		}

		throw std::runtime_error(module_name + " wasn't found");
	}

	inline DWORD pDevice;
	inline ClientEntityList* pEntityList;
	inline iBaseClient* pClient;
	inline i_client_mode* pClientMode;
	inline ModelInfo* pModelInfo;
	inline i_console* pConsole;
	inline iv_engine_client* pEngine;
	inline c_global_vars_base* pGlobals;
	inline iv_model_render* pModelRender;
	inline i_material_system* pMaterialSystem;
	inline glow_manager_t* pGlowManager;
	inline i_client_state* pClientState;

	void InitInterface();
}

#endif // !INTERFACE_HPP
