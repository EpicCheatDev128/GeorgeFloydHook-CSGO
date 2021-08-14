#include <iostream>
#include <string>
#include "Menu.h"
#include "Rendering.h"
#include "Math.h"

void Menu::InitMenu() {
    //NEXT LEFEL MENU
    Menu.emplace_back(MenuStruct(false, "GlowESP"));
    Menu.emplace_back(MenuStruct(false, "TriggerBot"));
    Menu.emplace_back(MenuStruct(true, "BunnyHop"));
    Menu.emplace_back(MenuStruct(true, "RCS"));
    Menu.emplace_back(MenuStruct("RCS Amount", true, 1.7f, 0.0f, 2.0f, 0.1f));
    Menu.emplace_back(MenuStruct("Chams", true, 2.0f, 0.0f, 2.0f, 1.0f));
    Menu.emplace_back(MenuStruct(false, "SnapLines"));
    Menu.emplace_back(MenuStruct(false, "HealthESP"));
    Menu.emplace_back(MenuStruct(true, "SkinChanger"));
    Menu.emplace_back(MenuStruct("ViewModel FOV", true, 90.0f, 54.0f, 160.0f, 1.0f));
    Menu.emplace_back(MenuStruct(true, "Grenade Pred"));
    Menu.emplace_back(MenuStruct(false, "Aimbot"));
    Menu.emplace_back(MenuStruct("Backtrack", true, 12.0f, 0.0f, 12.0f, 1.0f));
    Menu.emplace_back(MenuStruct(false, "Clantag Changer"));
    Menu.emplace_back(MenuStruct(true, "Reveal Ranks"));
}

void Menu::DrawMenu(IDirect3DDevice9* pDevice) {
    int textPosX = 300; int textPosY = 20;

    for (int i = 0; i < Menu.size(); i++) {
        if (!bMenu)
            continue;

        if (i + 1 == MenuControl) {
            std::string str = "> " + std::string(Menu[i].sText);
            Render::CText(str.c_str(), textPosX, textPosY, 4);
        }
        else
            Render::CText(Menu[i].sText, textPosX, textPosY, 3);

        if (Menu[i].bUseValue) {
            std::string str = std::to_string(Menu[i].fValue);
            Render::CText(str.c_str(), textPosX + 150, textPosY, 3);
        }
        else {
            if (Menu[i].bState)
                Render::CText("\tON", textPosX + 150, textPosY, 1);
            else
                Render::CText("\tOFF", textPosX + 150, textPosY, 2);
        }
        textPosY += 20;
    }
}