#include "Features.h"
#include <iostream>
#include <Windows.h>
#include <thread>
#include <chrono>
#include <vector>
#include "Offsets.h"
#include "Rendering.h"
#include "Interface.h"
#include "Globals.h"
#include "Menu.h"
#include "Entity.hpp"

void Features::ButtonHandling() {
    // Ако натиснете този бутон играта ви се крашне
    if (GetAsyncKeyState(VK_NUMPAD9)) ForceUpdate();

    if (GetAsyncKeyState(VK_INSERT) & 1)
        Menu::bMenu = !Menu::bMenu;

    if (Menu::bMenu) {
        if (GetAsyncKeyState(VK_NUMPAD8) & 1) {
            if (Menu::MenuControl > 1)
                Menu::MenuControl--;
            else
                Menu::MenuControl = 1;
        }
        if (GetAsyncKeyState(VK_NUMPAD2) & 1) {
            if (Menu::MenuControl < Menu::Menu.size())
                Menu::MenuControl++;
            else
                Menu::MenuControl = Menu::Menu.size();
        }

        if (Menu::Menu[Menu::MenuControl - 1].bUseValue) {
            if (GetAsyncKeyState(VK_NUMPAD4) & 1) {
                if (Menu::Menu[Menu::MenuControl - 1].fValue > Menu::Menu[Menu::MenuControl - 1].fMin)
                    Menu::Menu[Menu::MenuControl - 1].fValue -= Menu::Menu[Menu::MenuControl - 1].fIncrement;
                else
                    Menu::Menu[Menu::MenuControl - 1].fValue = Menu::Menu[Menu::MenuControl - 1].fMin;
            }

            if (GetAsyncKeyState(VK_NUMPAD6) & 1) {
                if (Menu::Menu[Menu::MenuControl - 1].fValue < Menu::Menu[Menu::MenuControl - 1].fMax)
                    Menu::Menu[Menu::MenuControl - 1].fValue += Menu::Menu[Menu::MenuControl - 1].fIncrement;
                else
                    Menu::Menu[Menu::MenuControl - 1].fValue = Menu::Menu[Menu::MenuControl - 1].fMax;
            }
        }
        else
            if (GetAsyncKeyState(VK_NUMPAD5) & 1)
                Menu::Menu[Menu::MenuControl - 1].bState = !Menu::Menu[Menu::MenuControl - 1].bState;
    }
}

player_t* Features::GetBestTarget(cUserCMD* cmd) {
    float maxDist = 180, currDist; player_t* target = NULL;
    for (int i = 1; i < Interfaces::pGlobals->max_clients; i++) {
        auto entity = reinterpret_cast<player_t*>(Interfaces::pEntityList->get_client_entity(i));

        if (!entity)
            continue;

        if (!entity->is_alive() || entity->dormant())
            continue;


        if (entity->team() != localPlayer->team()) {
            vec3_t localEyePos = localPlayer->get_eye_pos();
            vec3_t enemyBone = entity->get_bone_position(8);
            vec3_t angleTo = calcAngle(localEyePos, enemyBone);
            angleTo.clamp();

            currDist = cmd->viewangles.distance_to(angleTo);

            if (currDist < maxDist) {
                maxDist = currDist;
                target = entity;
            }
        }

    }
    return target;
}

void Features::AimBot(cUserCMD* cmd) {
    //лол
    if (!localPlayer || !Menu::Menu[11].bState) return;
    if (!GetAsyncKeyState(VK_MENU)) return;

    player_t* target = GetBestTarget(cmd);
    if (!target) return;

    vec3_t localEyePos = localPlayer->get_eye_pos();
    vec3_t targetBone = target->get_bone_position(8);
    vec3_t targetAngle = calcAngle(localEyePos, targetBone);

    targetAngle.clamp();
    vec3_t finalAng = targetAngle - localPlayer->aim_punch_angle() * 2.f;
    finalAng.clamp();

    Interfaces::pEngine->set_view_angles(finalAng);
}

void Features::RecoilControl(cUserCMD* cmd) {
    if (!Menu::Menu[3].bState || !localPlayer)
        return;
    //"Recoil Script" за да се минимизиря колко гярми калашник

    const auto dwPunchAngle = localPlayer->aim_punch_angle();
    const auto dwShotsFired = localPlayer->shots_fired();
    const auto dwViewAngle = cmd->viewangles;
    const auto totalPunch = dwPunchAngle.x + dwPunchAngle.y;

        if (totalPunch != 0.f)
        {
            if (dwShotsFired > 1)
            {
                auto NewAngles = vec3_t{ ((dwViewAngle.x + dwOldPunchAngle.x) - (dwPunchAngle.x * Menu::Menu[4].fValue)), ((dwViewAngle.y + dwOldPunchAngle.y) - (dwPunchAngle.y * Menu::Menu[4].fValue)), 0.f };

                NewAngles.normalize();
                NewAngles.clamp();

                Interfaces::pEngine->set_view_angles(NewAngles);
            }

            if (dwPunchAngle.x != 0.f)
                dwOldPunchAngle.x = dwPunchAngle.x * Menu::Menu[4].fValue;
            else
                dwOldPunchAngle.x = 0.f;

            if (dwPunchAngle.y != 0.f)
                dwOldPunchAngle.y = dwPunchAngle.y * Menu::Menu[4].fValue;
            else
                dwOldPunchAngle.y = 0.f;

        }
        else
            dwOldPunchAngle = vec3_t{ 0.f,0.f,0.f };
}

void Features::GlowESP() {
    if (!Menu::Menu[0].bState || !localPlayer)
        return;
    if (!Interfaces::pEngine->is_connected() || !Interfaces::pEngine->is_in_game())
        return;

    for (int i = 0; i < Interfaces::pGlowManager->size; ++i)
    {
        if (Interfaces::pGlowManager->objects[i].unused() || !Interfaces::pGlowManager->objects[i].entity)
            continue;

        auto& glowEnt = Interfaces::pGlowManager->objects[i];
        auto pCSPlayer = reinterpret_cast<player_t*>(glowEnt.entity);
        auto clientclass = reinterpret_cast<c_client_class*>(pCSPlayer->client_class());

        if (!pCSPlayer)
            continue;

        if (pCSPlayer == localPlayer)
            continue;

        if (clientclass->class_id == ccsplayer)
        {
            if (pCSPlayer->dormant())
                continue;
            if (!(pCSPlayer->is_alive() && pCSPlayer->health() > 0))
                continue;

            if (pCSPlayer->team() == localPlayer->team()) continue;

            glowEnt.set(1.0f, 0.0f, 0.0f, 0.8f);
        }
    }
}

void Features::TriggerBot() {
    if (!Menu::Menu[1].bState || !localPlayer)
        return;

    //fuck you
}

void Features::BunnyHop(cUserCMD* cmd) {
    if (!Menu::Menu[2].bState || !localPlayer || !Interfaces::pEngine->is_in_game() || !localPlayer->is_alive())
        return;

    if (!(localPlayer->flags() & FL_ONGROUND))
        cmd->buttons &= ~in_jump;
}

void Features::BasicESP(IDirect3DDevice9* pDevice) {
    if (!localPlayer)
        return;
    //Маикати е проститутка
    matrix = ReadProcMem<ViewMatrix>(baseModule + dwViewMatrix);
    for (int i = 1; i < Interfaces::pGlobals->max_clients; i++) {
        auto entity = reinterpret_cast<player_t*>(Interfaces::pEntityList->get_client_entity(i));

        if (!entity)
            continue;
        if (!entity->is_alive() || entity->dormant() || entity == localPlayer || entity->team() == localPlayer->team())
            continue;

        vec3_t entHead = WorldToScreen(entity->origin());
        
        if (entHead.z < 0.01f)
            continue;

        if (Menu::Menu[6].bState)
            Render::Line(SCREEN_WIDTH / 2, SCREEN_HEIGHT, entHead.x, entHead.y, 2, true, D3DCOLOR_ARGB(255, 255, 0, 0), pDevice);

        if (Menu::Menu[7].bState) {
            player_info_t pInfo;
            Interfaces::pEngine->get_player_info(i, &pInfo);

            std::string str = pInfo.name + (std::string)" | " + std::to_string(entity->health());
            Render::CText(str.c_str(), entHead.x, entHead.y + 10, 3);
        }
    }
}

void Features::ForceUpdate() {
    bUpdate = true;
    Interfaces::pClientState->full_update();    
}

void Features::SkinChanger() {
    if (!localPlayer || !Menu::Menu[8].bState || !localPlayer->is_alive()) return;

    auto allWeapons = localPlayer->get_weapons(); int paintKit = 0;

    for (int i = 0; i < 3; i++) {
        auto pWeapon = (weapon_t*)Interfaces::pEntityList->get_client_entity_handle(allWeapons[i]);
        if (!pWeapon) continue;

        id = pWeapon->item_definition_index();

        if (id == 0 || id > 64 || id == 49 || id == 42 || id == 59 || id == 508) continue;
        if (id == 43 || id == 44 || id == 45 || id == 46 || id == 47 || id == 48 || id == 49) continue;

        switch (id) {
        case 1: // deagle
            paintKit = 962;
            break;
        case 7: // калашник
            paintKit = 959;
            break;
        case 61: // usp
            paintKit = 313;
            break;
        case 60: // m4a1
            paintKit = 984;
            break;
        case 2: // dual
            paintKit = 658;
            break;
        case 32: // p2000
            paintKit = 389;
            break;
        case 9: // драгунов
            paintKit = 344;
            break;
        case 16: // m4a4
            paintKit = 309;
            break;
        case 4: // Glock
            paintKit = 963;
            break;
        case 3: // Five Seven
            paintKit = 660;
            break;
        case 8: // AUG
            paintKit = 455;
            break;
        case 10: // Famas
            paintKit = 919;
            break;
        case 11: // G3SG1
            paintKit = 511;
            break;
        case 13: // Galil
            paintKit = 428;
            break;
        case 14: // M249
            paintKit = 496;
            break;
        case 17: // Mac 10
            paintKit = 947;
            break;
        case 19: // P90
            paintKit = 283;
            break;
        case 24: // UMP-45
            paintKit = 556;
            break;
        case 25: // помпа
            paintKit = 654;
            break;
        case 26: // бесполезник
            paintKit = 676;
            break;
        case 27: // Mag 7
            paintKit = 39;
            break;
        case 28: // негер
            paintKit = 514;
            break;
        case 29: // Sawed Off
            paintKit = 638;
            break;
        case 30: // Tec 9
            paintKit = 889;
            break;
        case 33: // MP7
            paintKit = 481;
            break;
        case 34: // MP9
            paintKit = 910;
            break;
        case 35: // Nova
            paintKit = 537;
            break;
        case 36: // P250
            paintKit = 678;
            break;
        case 38: // Scar 20
            paintKit = 685;
            break;
        case 39: // SG553
            paintKit = 39;
            break;
        case 40: // патка
            paintKit = 624;
            break;
        }

        pWeapon->paint_kit() = paintKit;
        pWeapon->entity_quality() = 3;
        pWeapon->fallback_wear() = 0.0001f;
        pWeapon->item_id() = -1;
    }
}

void Features::KnifeChanger() {

    //краш
    if (!localPlayer || !Menu::Menu[8].bState || !localPlayer->is_alive())
        return;

        int model = Interfaces::pModelInfo->get_model_index("models/weapons/v_knife_m9_bay.mdl");
        short itemDefIndex = 508;


    auto allWeapons = localPlayer->get_weapons();

    for (int i = 0; i < 3; i++) {
        weapon_t* pWeapon = (weapon_t*)Interfaces::pEntityList->get_client_entity_handle(allWeapons[i]);
        if (!pWeapon) continue;
        base_view_model_t* pView = (base_view_model_t*)Interfaces::pEntityList->get_client_entity_handle(localPlayer->view_model());
        if (!pView) continue;
        auto pWeaponView = (weapon_t*)Interfaces::pEntityList->get_client_entity_handle(pView->weapon());
        if (!pWeaponView) continue;

        short knifeID = pWeapon->item_definition_index();

        if (knifeID == WEAPON_KNIFE || knifeID == WEAPON_KNIFE_T || knifeID == itemDefIndex) {
            if(pWeapon == pWeaponView)
                pView->set_model_index(model);
            pWeapon->set_model_index(model);

            pWeapon->item_definition_index() = itemDefIndex;
            pWeapon->paint_kit() = 562;
            pWeapon->entity_quality() = 3;
            pWeapon->fallback_wear() = 0.0001f;
            pWeapon->item_id() = -1;
        }
    }
}

void Features::GloveChanger() {
    //краш
    if (!localPlayer || !Menu::Menu[8].bState)
        return;

    if (!localPlayer->is_alive()) {
        auto pGlove = (weapon_t*)Interfaces::pEntityList->get_client_entity(localPlayer->get_wearables()[0] &0xFFF);
        if (!pGlove)
            return;

        pGlove->net_set_destroyed_on_recreate_entities();
        pGlove->net_release();
        return;
    }

    if(!glove)
        glove = Interfaces::pModelInfo->get_model_index("models/weapons/v_models/arms/glove_sport/v_glove_sport.mdl");

    if (bUpdate) {
        auto pGlove = (weapon_t*)Interfaces::pEntityList->get_client_entity(localPlayer->get_wearables()[0] & 0xFFF);
        if (!pGlove)
            for (c_client_class* pClass = Interfaces::pClient->get_client_classes(); pClass; pClass = pClass->next_ptr)
            {
                if (pClass->class_id != ceconwearable)
                    continue;

                int iEntry = (Interfaces::pEntityList->get_highest_index() + 1),
                    iSerial = rand() % (0x0 - 0xFFF + 1) + 0x0;

                pClass->create_fn(iEntry, iSerial);
                localPlayer->get_wearables()[0] = iEntry | (iSerial << 16);
                break;
            }

        auto pWearable = (weapon_t*)Interfaces::pEntityList->get_client_entity(localPlayer->get_wearables()[0] & 0xFFF);
        if (!pWearable) return;

        pWearable->set_model_index(glove);
        pWearable->item_definition_index() = 5030;
        pWearable->paint_kit() = 10047;
        pWearable->fallback_wear() = 0.29f;
        pWearable->item_id() = -1;
        pWearable->net_pre_data_update(0);
        bUpdate = false;
    }
}

void Features::GrenadePrediction() {
    if (!localPlayer || !localPlayer->is_alive())
        return;
    // тука исполсваме "cl_grenadepreview"  дето ебе ФПС когато имаш граната
    Interfaces::pConsole->get_convar("cl_grenadepreview")->set_value(Menu::Menu[10].bState);
}

void Features::ClantagChanger() {
    if (!localPlayer || !Interfaces::pEngine->is_in_game())
        return;

    if (Menu::Menu[13].bState && bOnce) {
        //георге флояд беше педерас
        localPlayer->SetClantag("GeorgeFloydHook");
        bOnce = false;
    }
    else if (!bOnce && !Menu::Menu[13].bState) {
        //краш
        localPlayer->SetClantag("");
        bOnce = true;
    }
}

void Features::OverrideMaterial(bool ignoreZ, const color& rgba, const char* mat) {

    i_material* material = nullptr; 
    material = Interfaces::pMaterialSystem->find_material(mat, TEXTURE_GROUP_OTHER);
    

    if (material == nullptr)
        material->increment_reference_count();
    
    material->set_material_var_flag(material_var_ignorez, ignoreZ);
    material->alpha_modulate(rgba.a / 255.0f);
    material->color_modulate(rgba.r / 255.0f, rgba.g / 255.0f, rgba.b / 255.0f);
    Interfaces::pModelRender->override_material(material);
}

void Features::BacktrackPlayer(cUserCMD* cmd) {
    if (Menu::Menu[12].fValue > 0.0f)
    {
        int nBestTargetIndex = -1;

        float flBestFov = FLT_MAX;

        if (!localPlayer->is_alive())
            return;

        for (int i = 1; i <= Interfaces::pGlobals->max_clients; i++)
        {
            auto pEntity = reinterpret_cast<player_t*>(Interfaces::pEntityList->get_client_entity(i));

            if (!pEntity || !localPlayer)
                continue;

            if (pEntity == localPlayer)
                continue;

            if (pEntity->dormant())
                continue;

            if (pEntity->team() == localPlayer->team())
                continue;

            if (pEntity->is_alive())
            {
                //краш
                float flSimulationTime = pEntity->simulation_time();

                vec3_t vecHeadPosition = pEntity->get_bone_position(8);

                Data[i][cmd->command_number % int(Menu::Menu[12].fValue)] = BacktrackingData{ flSimulationTime, vecHeadPosition };

                vec3_t ViewDir = AngleVector(cmd->viewangles + (localPlayer->aim_punch_angle() * 2.f));

                float FOVDistance = DistancePointToLine(vecHeadPosition, localPlayer->get_eye_pos(), ViewDir);

                if (flBestFov > FOVDistance)
                {
                    flBestFov = FOVDistance;
                    nBestTargetIndex = i;
                }
            }
        }


        float flBestTargetSimTime;
        if (nBestTargetIndex != -1)
        {
            float flTempFloat = FLT_MAX;
            vec3_t ViewDir = AngleVector(cmd->viewangles + (localPlayer->aim_punch_angle() * 2.f));
            for (int t = 0; t < (int)Menu::Menu[12].fValue; ++t)
            {
                float flTempFOVDistance = DistancePointToLine(Data[nBestTargetIndex][t].m_vecHitboxPosition, localPlayer->get_eye_pos(), ViewDir);
                if (flTempFloat > flTempFOVDistance && Data[nBestTargetIndex][t].m_flSimulationTime > localPlayer->simulation_time() - 1)
                {
                    flTempFloat = flTempFOVDistance;
                    flBestTargetSimTime = Data[nBestTargetIndex][t].m_flSimulationTime;
                }
            }

            if (cmd->buttons & in_attack && flBestTargetSimTime > 0)
                cmd->tick_count = (int)(0.5f + (float)(flBestTargetSimTime) / Interfaces::pGlobals->interval_per_tick);
        }
    }
}