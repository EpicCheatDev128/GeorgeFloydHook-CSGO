#include "Hooks.h"
#include "Entity.hpp"
#include "Offsets.h"

Hooks::endScene oEndScene;
Hooks::getViewModelFOV oViewModelFOV;
Hooks::CreateMove oCreateMove;
Hooks::DrawModelExecute oDrawModel;
Hooks::FrameStageNotify oFrameStage;

void Hooks::InitHooks() {
	auto viewModelTarget = *reinterpret_cast<void***>(Interfaces::pClientMode);
	auto endSceneTarget = *reinterpret_cast<void***>(Interfaces::pDevice);
    auto createMoveTarget = *reinterpret_cast<void***>(Interfaces::pClientMode);
	auto drawModelTarget = *reinterpret_cast<void***>(Interfaces::pModelRender);
	auto frameStageTarget = *reinterpret_cast<void***>(Interfaces::pClient);

	oViewModelFOV = (getViewModelFOV)DetourFunction((PBYTE)viewModelTarget[35], (PBYTE)hookedViewModel);
	oEndScene = (endScene)DetourFunction((PBYTE)endSceneTarget[42], (PBYTE)hookedEndScene);
    oCreateMove = (CreateMove)DetourFunction((PBYTE)createMoveTarget[24], (PBYTE)hookedCreateMove);
	oDrawModel = (DrawModelExecute)DetourFunction((PBYTE)drawModelTarget[21], (PBYTE)hookedDrawModel);
	oFrameStage = (FrameStageNotify)DetourFunction((PBYTE)frameStageTarget[37], (PBYTE)hookedFrameStage);
}

float __stdcall Hooks::hookedViewModel() {
	return Menu::Menu[9].fValue;
}

HRESULT __stdcall Hooks::hookedEndScene(IDirect3DDevice9* pDevice) {
    if (!Render::font)
        D3DXCreateFont(pDevice, 16, 0, FW_HEAVY, 1, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Arial", &Render::font);

    Menu::DrawMenu(pDevice);
    Features::BasicESP(pDevice);
	Features::GlowESP();

    return oEndScene(pDevice);
}

bool __stdcall Hooks::hookedCreateMove(float sampleFrameRate, cUserCMD* cmd) {
    oCreateMove(sampleFrameRate, cmd);

	localPlayer = static_cast<player_t*>(Interfaces::pEntityList->get_client_entity(Interfaces::pEngine->get_local_player()));
	
	if (!cmd || !cmd->command_number)
		return false;

	uintptr_t* frame_pointer;
	__asm mov frame_pointer, ebp;
	bool& send_packet = *reinterpret_cast<bool*>(*frame_pointer - 0x1C);

	auto old_viewangles = cmd->viewangles;
	auto old_forwardmove = cmd->forwardmove;
	auto old_sidemove = cmd->sidemove;

	Features::BacktrackPlayer(cmd);
	Features::BunnyHop(cmd);
	Features::RecoilControl(cmd);
	Features::AimBot(cmd);
	if (Menu::Menu[14].bState) { Features::RankRevealAll(cmd); }


	cmd->forwardmove = std::clamp(cmd->forwardmove, -450.0f, 450.0f);
	cmd->sidemove = std::clamp(cmd->sidemove, -450.0f, 450.0f);
	cmd->upmove = std::clamp(cmd->upmove, -320.0f, 320.0f);

	cmd->viewangles.normalize();
	cmd->viewangles.x = std::clamp(cmd->viewangles.x, -89.0f, 89.0f);
	cmd->viewangles.y = std::clamp(cmd->viewangles.y, -180.0f, 180.0f);
	cmd->viewangles.z = 0.0f;

	return false;
}

void DrawChams(i_mat_render_context* ctx, const draw_model_state_t& state, const model_render_info_t& info, matrix_t* matrix)
{
	const auto mdl = info.model;

	bool is_arm = strstr(mdl->name, "arms") != nullptr;
	bool is_player = strstr(mdl->name, "models/player") != nullptr;
	bool is_sleeve = strstr(mdl->name, "sleeve") != nullptr;
	bool is_weapon = strstr(mdl->name, "weapons/v_") != nullptr;

	const auto clr_front = color(0.f, 255.f, 0.f);
	const auto clr_back = color(255.f, 0.f, 0.f);
	const auto emp_front = color(1.f, 1.f, 1.f, 0.0f);

	if (is_player && Menu::Menu[5].fValue > 0.0f) {

		player_t* player = reinterpret_cast<player_t*>(Interfaces::pEntityList->get_client_entity(info.entity_index));;

		if (player && localPlayer && player->is_alive()) {
			if (player->team() == localPlayer->team())
				return;
			if (Menu::Menu[5].fValue == 1.0f) {
				Features::OverrideMaterial(true, clr_back, "debug/debugambientcube");
				oDrawModel(Interfaces::pModelRender, 0, ctx, state, info, matrix);
			}
			Features::OverrideMaterial(false, clr_front, "debug/debugambientcube");
		}
	}
	else if (is_sleeve && Menu::Menu[5].bState && localPlayer) {
		Features::OverrideMaterial(false, emp_front, "debug/debugambientcube");
		oDrawModel(Interfaces::pModelRender, 0, ctx, state, info, matrix);
	}
};

void __fastcall Hooks::hookedDrawModel(void* _this, int edx, i_mat_render_context* ctx, const draw_model_state_t& state, const model_render_info_t& pInfo, matrix_t* pCustomBoneToWorld) {
	if (Interfaces::pEngine->is_in_game() && Interfaces::pEngine->is_connected() && localPlayer) {

		if (!Interfaces::pModelRender->is_forced()) {
			DrawChams(ctx, state, pInfo, pCustomBoneToWorld);
			oDrawModel(_this, edx, ctx, state, pInfo, pCustomBoneToWorld);
			Interfaces::pModelRender->override_material(nullptr);
		}
		else
			oDrawModel(_this, edx, ctx, state, pInfo, pCustomBoneToWorld);
	}
}

void __fastcall Hooks::hookedFrameStage(int ecx, int edx, client_frame_stage_t stage) {
	if (Interfaces::pEngine->is_in_game() && Interfaces::pEngine->is_connected() && localPlayer) {

		if (stage == FRAME_NET_UPDATE_POSTDATAUPDATE_START) {
			Features::GrenadePrediction();
			Features::ClantagChanger();
			Features::SkinChanger();
			Features::KnifeChanger();
			Features::GloveChanger();
		}
	}
	return oFrameStage(ecx, stage);
}

void Hooks::Release() {
    DetourRemove((PBYTE)oEndScene, (PBYTE)hookedEndScene);
    DetourRemove((PBYTE)oViewModelFOV, (PBYTE)hookedViewModel);
	DetourRemove((PBYTE)oCreateMove, (PBYTE)hookedCreateMove);
	DetourRemove((PBYTE)oDrawModel, (PBYTE)hookedDrawModel);
	DetourRemove((PBYTE)oFrameStage, (PBYTE)hookedFrameStage);
}
