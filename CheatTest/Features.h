#pragma once
#ifndef FEATURES_H
#define FEATURES_H

#include <d3d9.h>
#include <d3dx9.h>

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

#include "Globals.h"
#include "Entity.hpp"

namespace Features {
    void ButtonHandling();
    inline static vec3_t dwOldPunchAngle;
    void RecoilControl(cUserCMD* cmd);

    void GlowESP();

    void TriggerBot();

    void BunnyHop(cUserCMD* cmd);
    inline DWORD dwViewMatrixA = FindPattern("client.dll", "0F 10 05 ? ? ? ? 8D 85 ? ? ? ? B9");
    void BasicESP(IDirect3DDevice9* pDevice);

    void ForceUpdate();
    inline short id;
    void SkinChanger();
    inline short knifeID;
    void KnifeChanger();
    inline bool bUpdate = true;
    inline int glove = NULL;
    void GloveChanger();

    void GrenadePrediction();

    player_t* GetBestTarget(cUserCMD* cmd);

    void AimBot(cUserCMD* cmd);

    void BacktrackPlayer(cUserCMD* cmd);
    inline bool bOnce = true;
    void ClantagChanger();

    void OverrideMaterial(bool, const color&, const char*);

    inline void RankRevealAll(cUserCMD* cmd)
    {
        if ((cmd->buttons & in_score) != 0)
            Interfaces::pClient->dispatch_user_message(50, 0, 0, nullptr);
    }
}


#endif // !FEATURES_H

