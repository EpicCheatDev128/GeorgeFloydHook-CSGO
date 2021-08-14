#pragma once
#ifndef HOOKS
#define HOOKS

#include <d3d9.h>
#include <d3dx9.h>

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

#include "detours.h"
#pragma comment(lib, "detours.lib")

#include "Math.h"
#include "Menu.h"
#include "Features.h"
#include "Rendering.h"
#include "Interface.h"
#include "Entity.hpp"

namespace Hooks {
	void InitHooks();
	void Release();

	typedef HRESULT(__stdcall* endScene)(IDirect3DDevice9* pDevice);
	typedef float(__stdcall* getViewModelFOV)();
	typedef bool(__stdcall* CreateMove)(float sampleFrameRate, cUserCMD* cmd);
	typedef void(__fastcall* DrawModelExecute)(void* _this, int edx, i_mat_render_context* ctx, const draw_model_state_t& state, const model_render_info_t& pInfo, matrix_t* pCustomBoneToWorld);
	typedef void(__thiscall* FrameStageNotify)(int, client_frame_stage_t stage);

	HRESULT __stdcall hookedEndScene(IDirect3DDevice9* pDevice);
	float __stdcall hookedViewModel();
	bool __stdcall hookedCreateMove(float sampleFrameRate, cUserCMD* cmd);
	void __fastcall hookedDrawModel(void* _this, int edx, i_mat_render_context* ctx, const draw_model_state_t& state, const model_render_info_t& pInfo, matrix_t* pCustomBoneToWorld);
	void __fastcall hookedFrameStage(int ecx, int edx, client_frame_stage_t stage);
}

#endif // !HOOKS
