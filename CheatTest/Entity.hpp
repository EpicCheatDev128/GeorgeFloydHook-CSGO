#pragma once
#include <array>
#include "ClientClass.hpp"
#include "Netvars.hpp"
#include "vector3d.hpp"
#include "Patternscanning.h"
#include "Globals.h"
#include "Interface.h"
#include "Math.h"

class collideable_t {
public:
	vec3_t& mins() {
		using original_fn = vec3_t & (__thiscall*)(void*);
		return (*(original_fn**)this)[1](this);
	}
	vec3_t& maxs() {
		using original_fn = vec3_t & (__thiscall*)(void*);
		return (*(original_fn**)this)[2](this);
	}
};

class anim_state {
public:
	char	u0[0x18];
	float	anim_update_timer;
	char	u1[0xC];
	float	started_moving_time;
	float	last_move_time;
	char	u2[0x10];
	float	last_lby_time;
	char	u3[0x8];
	float	run_amount;
	char	u4[0x10];
	void* entity;
	__int32 active_weapon;
	__int32 last_active_weapon;
	float	last_clientside_anim_update_time;
	__int32 last_clientside_anim_update_framecount;
	float	eye_timer;
	float	eye_angles_y;
	float	eye_angles_x;
	float	goal_feet_yaw;
	float	current_feet_yaw;
	float	torso_yaw;
	float	last_move_yaw;
	float	lean_amount;
	char	u5[0x4];
	float	feet_cycle;
	float	feet_yaw_rate;
	char	u6[0x4];
	float	duck_amount;
	float	landing_duck_amount;
	char	u7[0x4];
	vec3_t	current_origin;
	vec3_t	last_origin;
	float	velocity_x;
	float	velocity_y;
	char	u8[0x10];
	float	move_direction_1;
	float	move_direction_2;
	char	u9[0x4];
	float	velocity;
	float	jump_fall_velocity;
	float	clamped_velocity;
	float	feet_speed_forwards_or_sideways;
	float	feet_speed_unknown_forwards_or_sideways;
	float	last_time_started_moving;
	float	last_time_stopped_moving;
	bool	on_ground;
	bool	hit_in_ground_anim;
	char	u10[0x4];
	float	last_origin_z;
	float	head_from_ground_distance_standing;
	float	stop_to_full_running_fraction;
	char	u11[0x14];
	__int32 is_not_moving;
	char	u12[0x20];
	float	last_anim_update_time;
	float	moving_direction_x;
	float	moving_direction_y;
	float	moving_direction_z;
	char	u13[0x44];
	__int32 started_moving;
	char	u14[0x8];
	float	lean_yaw;
	char	u15[0x8];
	float	poses_speed;
	char	u16[0x8];
	float	ladder_speed;
	char	u17[0x8];
	float	ladder_yaw;
	char	u18[0x8];
	float	some_pose;
	char	u19[0x14];
	float	body_yaw;
	char	u20[0x8];
	float	body_pitch;
	char	u21[0x8];
	float	death_yaw;
	char	u22[0x8];
	float	stand;
	char	u23[0x8];
	float	jump_fall;
	char	u24[0x8];
	float	aim_blend_stand_idle;
	char	u25[0x8];
	float	aim_blend_crouch_idle;
	char	u26[0x8];
	float	strafe_yaw;
	char	u27[0x8];
	float	aim_blend_stand_walk;
	char	u28[0x8];
	float	aim_blend_stand_run;
	char	u29[0x8];
	float	aim_blend_crouch_walk;
	char	u30[0x8];
	float	move_blend_walk;
	char	u31[0x8];
	float	move_blend_run;
	char	u32[0x8];
	float	move_blend_crouch;
	char	u33[0x4];
	float	speed;
	__int32 moving_in_any_direction;
	float	acceleration;
	char	u34[0x74];
	float	crouch_height;
	__int32 is_full_crouched;
	char	u35[0x4];
	float	velocity_subtract_x;
	float	velocity_subtract_y;
	float	velocity_subtract_z;
	float	standing_head_height;
};


enum data_update_type_t {
	DATA_UPDATE_CREATED = 0,
	DATA_UPDATE_DATATABLE_CHANGED,
};

enum cs_weapon_type {
	WEAPONTYPE_KNIFE = 0,
	WEAPONTYPE_PISTOL,
	WEAPONTYPE_SUBMACHINEGUN,
	WEAPONTYPE_RIFLE,
	WEAPONTYPE_SHOTGUN,
	WEAPONTYPE_SNIPER_RIFLE,
	WEAPONTYPE_MACHINEGUN,
	WEAPONTYPE_C4,
	WEAPONTYPE_PLACEHOLDER,
	WEAPONTYPE_GRENADE,
	WEAPONTYPE_UNKNOWN
};

enum client_frame_stage_t {
	FRAME_UNDEFINED = -1,			// (haven't run any frames yet)
	FRAME_START,

	// A network packet is being recieved
	FRAME_NET_UPDATE_START,
	// Data has been received and we're going to start calling PostDataUpdate
	FRAME_NET_UPDATE_POSTDATAUPDATE_START,
	// Data has been received and we've called PostDataUpdate on all data recipients
	FRAME_NET_UPDATE_POSTDATAUPDATE_END,
	// We've received all packets, we can now do interpolation, prediction, etc..
	FRAME_NET_UPDATE_END,

	// We're about to start rendering the scene
	FRAME_RENDER_START,
	// We've finished rendering the scene.
	FRAME_RENDER_END
};

enum move_type {
	movetype_none = 0,
	movetype_isometric,
	movetype_walk,
	movetype_step,
	movetype_fly,
	movetype_flygravity,
	movetype_vphysics,
	movetype_push,
	movetype_noclip,
	movetype_ladder,
	movetype_observer,
	movetype_custom,
	movetype_last = movetype_custom,
	movetype_max_bits = 4,
	max_movetype
};

enum entity_flags {
	fl_onground = (1 << 0),
	fl_ducking = (1 << 1),
	fl_waterjump = (1 << 2),
	fl_ontrain = (1 << 3),
	fl_inrain = (1 << 4),
	fl_frozen = (1 << 5),
	fl_atcontrols = (1 << 6),
	fl_client = (1 << 7),
	fl_fakeclient = (1 << 8),
	fl_inwater = (1 << 9),
	fl_fly = (1 << 10),
	fl_swim = (1 << 11),
	fl_conveyor = (1 << 12),
	fl_npc = (1 << 13),
	fl_godmode = (1 << 14),
	fl_notarget = (1 << 15),
	fl_aimtarget = (1 << 16),
	fl_partialground = (1 << 17),
	fl_staticprop = (1 << 18),
	fl_graphed = (1 << 19),
	fl_grenade = (1 << 20),
	fl_stepmovement = (1 << 21),
	fl_donttouch = (1 << 22),
	fl_basevelocity = (1 << 23),
	fl_worldbrush = (1 << 24),
	fl_object = (1 << 25),
	fl_killme = (1 << 26),
	fl_onfire = (1 << 27),
	fl_dissolving = (1 << 28),
	fl_transragdoll = (1 << 29),
	fl_unblockable_by_player = (1 << 30)
};
enum item_definition_indexes {
	WEAPON_NONE = 0,
	WEAPON_DEAGLE,
	WEAPON_ELITE,
	WEAPON_FIVESEVEN,
	WEAPON_GLOCK,
	WEAPON_AK47 = 7,
	WEAPON_AUG,
	WEAPON_AWP,
	WEAPON_FAMAS,
	WEAPON_G3SG1,
	WEAPON_GALILAR = 13,
	WEAPON_M249,
	WEAPON_M4A1 = 16,
	WEAPON_MAC10,
	WEAPON_P90 = 19,
	WEAPON_MP5SD = 23,
	WEAPON_UMP45,
	WEAPON_XM1014,
	WEAPON_BIZON,
	WEAPON_MAG7,
	WEAPON_NEGEV,
	WEAPON_SAWEDOFF,
	WEAPON_TEC9,
	WEAPON_TASER,
	WEAPON_HKP2000,
	WEAPON_MP7,
	WEAPON_MP9,
	WEAPON_NOVA,
	WEAPON_P250,
	WEAPON_SHIELD,
	WEAPON_SCAR20,
	WEAPON_SG556,
	WEAPON_SSG08,
	WEAPON_KNIFEGG,
	WEAPON_KNIFE,
	WEAPON_FLASHBANG,
	WEAPON_HEGRENADE,
	WEAPON_SMOKEGRENADE,
	WEAPON_MOLOTOV,
	WEAPON_DECOY,
	WEAPON_INCGRENADE,
	WEAPON_C4,
	WEAPON_HEALTHSHOT = 57,
	WEAPON_KNIFE_T = 59,
	WEAPON_M4A1_SILENCER,
	WEAPON_USP_SILENCER,
	WEAPON_CZ75A = 63,
	WEAPON_REVOLVER,
	WEAPON_TAGRENADE = 68,
	WEAPON_FISTS,
	WEAPON_BREACHCHARGE,
	WEAPON_TABLET = 72,
	WEAPON_MELEE = 74,
	WEAPON_AXE,
	WEAPON_HAMMER,
	WEAPON_SPANNER = 78,
	WEAPON_KNIFE_GHOST = 80,
	WEAPON_FIREBOMB,
	WEAPON_DIVERSION,
	WEAPON_FRAG_GRENADE,
	WEAPON_SNOWBALL,
	WEAPON_BUMPMINE,
	WEAPON_BAYONET = 500,
	WEAPON_KNIFE_CSS = 503,
	WEAPON_KNIFE_FLIP = 505,
	WEAPON_KNIFE_GUT,
	WEAPON_KNIFE_KARAMBIT,
	WEAPON_KNIFE_M9_BAYONET,
	WEAPON_KNIFE_TACTICAL,
	WEAPON_KNIFE_FALCHION = 512,
	WEAPON_KNIFE_SURVIVAL_BOWIE = 514,
	WEAPON_KNIFE_BUTTERFLY,
	WEAPON_KNIFE_PUSH,
	WEAPON_KNIFE_URSUS = 519,
	WEAPON_KNIFE_GYPSY_JACKKNIFE,
	WEAPON_KNIFE_STILETTO = 522,
	WEAPON_KNIFE_WIDOWMAKER,
	GLOVE_STUDDED_BLOODHOUND = 5027,
	GLOVE_T_SIDE = 5028,
	GLOVE_CT_SIDE = 5029,
	GLOVE_SPORTY = 5030,
	GLOVE_SLICK = 5031,
	GLOVE_LEATHER_WRAP = 5032,
	GLOVE_MOTORCYCLE = 5033,
	GLOVE_SPECIALIST = 5034,
	GLOVE_HYDRA = 5035
};

class entity_t {
public:
	void* animating() {
		return reinterpret_cast<void*>(uintptr_t(this) + 0x4);
	}
	void* networkable() {
		return reinterpret_cast<void*>(uintptr_t(this) + 0x8);
	}
	collideable_t* collideable() {
		using original_fn = collideable_t * (__thiscall*)(void*);
		return (*(original_fn**)this)[3](this);
	}
	c_client_class* client_class() {
		using original_fn = c_client_class * (__thiscall*)(void*);
		return (*(original_fn**)networkable())[2](networkable());
	}

	int index() {
		using original_fn = int(__thiscall*)(void*);
		return (*(original_fn**)networkable())[10](networkable());
	}
	bool is_player() {
		using original_fn = bool(__thiscall*)(entity_t*);
		return (*(original_fn**)this)[157](this);
	}
	bool is_weapon() {
		using original_fn = bool(__thiscall*)(entity_t*);
		return (*(original_fn**)this)[165](this);
	}
	bool setup_bones(matrix_t* out, int max_bones, int mask, float time) {
		if (!this)
			return false;

		using original_fn = bool(__thiscall*)(void*, matrix_t*, int, int, float);
		return (*(original_fn**)animating())[13](animating(), out, max_bones, mask, time);
	}
	model_t* model() {
		using original_fn = model_t * (__thiscall*)(void*);
		return (*(original_fn**)animating())[8](animating());
	}
	void update() {
		using original_fn = void(__thiscall*)(entity_t*);
		(*(original_fn**)this)[218](this);
	}
	int draw_model(int flags, uint8_t alpha) {
		using original_fn = int(__thiscall*)(void*, int, uint8_t);
		return (*(original_fn**)animating())[9](animating(), flags, alpha);
	}
	void set_angles(vec3_t angles) {
		using original_fn = void(__thiscall*)(void*, const vec3_t&);
		static original_fn set_angles_fn = (original_fn)((DWORD)FindPattern("client.dll", "55 8B EC 83 E4 F8 83 EC 64 53 56 57 8B F1"));
		set_angles_fn(this, angles);
	}
	void set_position(vec3_t position) {
		using original_fn = void(__thiscall*)(void*, const vec3_t&);
		static original_fn set_position_fn = (original_fn)((DWORD)FindPattern("client.dll", "55 8B EC 83 E4 F8 51 53 56 57 8B F1 E8"));
		set_position_fn(this, position);
	}

	int* ViewModelIndex()
	{
		return (int*)((uintptr_t)this + netvar_manager::get_net_var(fnv::hash("DT_BaseCombatWeapon"), fnv::hash("m_iViewModelIndex")));
	}

	int* ModelIndex()
	{
		return (int*)((uintptr_t)this + netvar_manager::get_net_var(fnv::hash("DT_BaseViewModel"), fnv::hash("m_nModelIndex")));
	}
	void set_model_index(int index) {
		using original_fn = void(__thiscall*)(void*, int);
		return (*(original_fn**)this)[75](this, index);
	}

	void net_pre_data_update(int update_type) {
		using original_fn = void(__thiscall*)(void*, int);
		return (*(original_fn**)networkable())[6](networkable(), update_type);
	}

	void net_release() {
		using original_fn = void(__thiscall*)(void*);
		return (*(original_fn**)networkable())[1](networkable());
	}

	int net_set_destroyed_on_recreate_entities() {
		using original_fn = int(__thiscall*)(void*);
		return (*(original_fn**)networkable())[13](networkable());
	}

	bool dormant() {
		using original_fn = bool(__thiscall*)(void*);
		return (*static_cast<original_fn**>(networkable()))[9](networkable());
	}

	NETVAR("DT_CSPlayer", "m_fFlags", flags, int)
		NETVAR("DT_BaseEntity", "m_hOwnerEntity", owner_handle, unsigned long)
		NETVAR("DT_CSPlayer", "m_flSimulationTime", simulation_time, float)
		NETVAR("DT_BasePlayer", "m_vecOrigin", origin, vec3_t)
		NETVAR("DT_BasePlayer", "m_vecViewOffset[0]", view_offset, vec3_t)
		NETVAR("DT_CSPlayer", "m_iTeamNum", team, int)
		NETVAR("DT_BaseEntity", "m_bSpotted", spotted, bool)
		NETVAR("DT_CSPlayer", "m_nSurvivalTeam", survival_team, int)
		NETVAR("DT_CSPlayer", "m_flHealthShotBoostExpirationTime", health_boost_time, float)
};

class econ_view_item_t {
public:
	NETVAR("DT_ScriptCreatedItem", "m_bInitialized", is_initialized, bool)
		NETVAR("DT_ScriptCreatedItem", "m_iEntityLevel", entity_level, int)
		NETVAR("DT_ScriptCreatedItem", "m_iAccountID", account_id, int)
		NETVAR("DT_ScriptCreatedItem", "m_iItemIDLow", item_id_low, int)
};

class base_view_model_t : public entity_t {
public:
	NETVAR("DT_BaseViewModel", "m_nModelIndex", model_index, int)
		NETVAR("DT_BaseViewModel", "m_nViewModelIndex", view_model_index, int)
		NETVAR("DT_BaseViewModel", "m_hWeapon", weapon, int)
		NETVAR("DT_BaseViewModel", "m_hOwner", owner, int)
};

class weapon_t : public entity_t {
private:
	template <typename T>
	T& read(uintptr_t offset) {
		return *reinterpret_cast<T*>(reinterpret_cast<uintptr_t>(this) + offset);
	}
public:

	NETVAR("DT_BaseCombatWeapon", "m_flNextPrimaryAttack", next_primary_attack, float)
		NETVAR("DT_BaseCombatWeapon", "m_flNextSecondaryAttack", next_secondary_attack, float)
		NETVAR("DT_BaseCombatWeapon", "m_iClip1", clip1_count, int)
		NETVAR("DT_BaseCombatWeapon", "m_iClip2", clip2_count, int)
		NETVAR("DT_BaseCombatWeapon", "m_iPrimaryReserveAmmoCount", primary_reserve_ammo_acount, int)
		NETVAR("DT_WeaponCSBase", "m_flRecoilIndex", recoil_index, float)
		NETVAR("DT_WeaponCSBaseGun", "m_zoomLevel", zoom_level, float)
		NETVAR("DT_BaseAttributableItem", "m_iItemDefinitionIndex", item_definition_index, short)
		NETVAR("DT_BaseAttributableItem", "m_iEntityQuality", entity_quality, int)
		NETVAR("DT_BaseAttributableItem", "m_iItemIDHigh", item_id, int)
		NETVAR("DT_BaseAttributableItem", "m_nFallbackPaintKit", paint_kit, int)
		NETVAR("DT_BaseAttributableItem", "m_flFallbackWear", fallback_wear, float)
		NETVAR("DT_BaseAttributableItem", "m_nFallbackStatTrak", stat_track, int)
		NETVAR("DT_BaseAttributableItem", "m_nFallbackSeed", seed, int)
		NETVAR("DT_BaseAttributableItem", "m_iAccountID", account_id, int)

		float inaccuracy() {
		using original_fn = float(__thiscall*)(void*);
		return (*(original_fn**)this)[482](this);
	}

	float get_spread() {
		using original_fn = float(__thiscall*)(void*);
		return (*(original_fn**)this)[452](this);
	}

	void update_accuracy_penalty() {
		using original_fn = void(__thiscall*)(void*);
		(*(original_fn**)this)[483](this);
	}
	short ItemDefIndex() {
		return read<short>((uintptr_t)this + netvar_manager::get_net_var(fnv::hash("DT_BaseAttributableItem"), fnv::hash("m_iItemDefinitionIndex")));
	}
};

class player_t : public entity_t {
private:
	template <typename T>
	T& read(uintptr_t offset) {
		return *reinterpret_cast<T*>(reinterpret_cast<uintptr_t>(this) + offset);
	}

	template <typename T>
	void write(uintptr_t offset, T data) {
		*reinterpret_cast<T*>(reinterpret_cast<uintptr_t>(this) + offset) = data;
	}

public:
	NETVAR("DT_BasePlayer", "m_hViewModel[0]", view_model, int)
		NETVAR("DT_CSPlayer", "m_bHasDefuser", has_defuser, bool)
		NETVAR("DT_CSPlayer", "m_bGunGameImmunity", has_gun_game_immunity, bool)
		NETVAR("DT_CSPlayer", "m_iShotsFired", shots_fired, int)
		NETVAR("DT_CSPlayer", "m_angEyeAngles", eye_angles, vec3_t)
		NETVAR("DT_CSPlayer", "m_ArmorValue", armor, int)
		NETVAR("DT_CSPlayer", "m_bHasHelmet", has_helmet, bool)
		NETVAR("DT_CSPlayer", "m_bIsScoped", is_scoped, bool)
		NETVAR("DT_CSPlayer", "m_bIsDefusing", is_defusing, bool)
		NETVAR("DT_CSPlayer", "m_iAccount", money, int)
		NETVAR("DT_CSPlayer", "m_flLowerBodyYawTarget", lower_body_yaw, float)
		NETVAR("DT_CSPlayer", "m_flNextAttack", next_attack, float)
		NETVAR("DT_CSPlayer", "m_flFlashDuration", flash_duration, float)
		NETVAR("DT_CSPlayer", "m_flFlashMaxAlpha", flash_alpha, float)
		NETVAR("DT_CSPlayer", "m_bHasNightVision", has_night_vision, bool)
		NETVAR("DT_CSPlayer", "m_bNightVisionOn", night_vision_on, bool)
		NETVAR("DT_CSPlayer", "m_iHealth", health, int)
		NETVAR("DT_CSPlayer", "m_lifeState", life_state, int)
		NETVAR("DT_CSPlayer", "m_fFlags", flags, int)
		NETVAR("DT_BasePlayer", "m_viewPunchAngle", punch_angle, vec3_t)
		NETVAR("DT_BasePlayer", "m_aimPunchAngle", aim_punch_angle, vec3_t)
		NETVAR("DT_BasePlayer", "m_vecVelocity[0]", velocity, vec3_t)
		NETVAR("DT_BasePlayer", "m_flMaxspeed", max_speed, float)
		NETVAR("DT_BaseEntity", "m_flShadowCastDistance", fov_time, float)
		NETVAR("DT_BasePlayer", "m_hObserverTarget", observer_target, unsigned long)
		NETVAR("DT_BasePlayer", "m_nHitboxSet", hitbox_set, int)
		NETVAR("DT_CSPlayer", "m_flDuckAmount", duck_amount, float)
		NETVAR("DT_CSPlayer", "m_bHasHeavyArmor", has_heavy_armor, bool)
		NETVAR("DT_SmokeGrenadeProjectile", "m_nSmokeEffectTickBegin", smoke_grenade_tick_begin, int)
		NETVAR("DT_CSPlayer", "m_nTickBase", get_tick_base, int)

		weapon_t* active_weapon() {
		auto active_weapon = read<uintptr_t>(netvar_manager::get_net_var(fnv::hash("DT_CSPlayer"), fnv::hash("m_hActiveWeapon"))) & 0xFFF;
		return reinterpret_cast<weapon_t*>(Interfaces::pEntityList->get_client_entity(active_weapon));
	}

	UINT* get_wearables() {
		return (UINT*)((uintptr_t)this + (netvar_manager::get_net_var(fnv::hash("DT_CSPlayer"), fnv::hash("m_hMyWearables"))));
	}

	UINT* get_weapons() {
		return (UINT*)((uintptr_t)this + (netvar_manager::get_net_var(fnv::hash("DT_CSPlayer"), fnv::hash("m_hMyWeapons"))));
	}

	vec3_t get_eye_pos() {
		return origin() + view_offset();
	}

	anim_state* get_anim_state() {
		return *reinterpret_cast<anim_state**>(this + 0x3914);
	}

	vec3_t get_bone_position(int bone) {
		matrix_t bone_matrices[128];
		if (setup_bones(bone_matrices, 128, 256, 0.0f))
			return vec3_t{ bone_matrices[bone][0][3], bone_matrices[bone][1][3], bone_matrices[bone][2][3] };
		else
			return vec3_t{ };
	}

	vec3_t get_hitbox_position(int hitbox_id) {
		matrix_t bone_matrix[MAXSTUDIOBONES];

		if (setup_bones(bone_matrix, MAXSTUDIOBONES, BONE_USED_BY_HITBOX, 0.0f)) {
			auto studio_model = Interfaces::pModelInfo->get_studio_model(model());

			if (studio_model) {
				auto hitbox = studio_model->hitbox_set(0)->hitbox(hitbox_id);

				if (hitbox) {
					auto min = vec3_t{}, max = vec3_t{};

					TransformVector(hitbox->mins, bone_matrix[hitbox->bone], min);
					TransformVector(hitbox->maxs, bone_matrix[hitbox->bone], max);

					return vec3_t((min.x + max.x) * 0.5f, (min.y + max.y) * 0.5f, (min.z + max.z) * 0.5f);
				}
			}
		}
		return vec3_t{};
	}

	bool is_alive() {
		if (!this) return false;
		return this->health() > 0;
	}

	bool is_moving() {
		if (!this) return false;
		return this->velocity().length() > 0.1f;
	}

	bool is_in_air() {
		if (!this) return false;
		return !(this->flags() & fl_onground);
	}

	bool is_flashed() {
		if (!this) return false;
		return this->flash_duration() > 0.0f;
	}

	void update_client_side_animations() {
		using original_fn = void(__thiscall*)(void*);
		(*(original_fn**)this)[223](this);
	}

	vec3_t& abs_origin() {
		using original_fn = vec3_t & (__thiscall*)(void*);
		return (*(original_fn**)this)[10](this);;
	}
	vec3_t& abs_angles() {
		using original_fn = vec3_t & (__thiscall*)(void*);
		return (*(original_fn**)this)[11](this);;
	}

	int move_type() {
		static int type = netvar_manager::get_net_var(fnv::hash("DT_BaseEntity"), fnv::hash("m_nRenderMode")) + 1;
		return read<int>(type);
	}

	void SetClantag(const char* tag)
	{
		static auto fnClantagChanged = (int(__fastcall*)(const char*, const char*))FindPattern("engine.dll", "53 56 57 8B DA 8B F9 FF 15");
		fnClantagChanged(tag, tag);
	}
	
};
