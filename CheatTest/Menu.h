#pragma once
#ifndef MENU
#define MENU

#include <iostream>
#include <vector>

#include <d3d9.h>
#include <d3dx9.h>

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

namespace Menu {
    struct MenuStruct {
        MenuStruct(bool b, LPCSTR s) {
            bState = b;
            sText = s;
            bUseValue = false;
            fValue = 0.0f;
            fMin = 0.0f;
            fMax = 0.0f;
        }

        MenuStruct(LPCSTR s, bool bu, float f, float min, float max, float inc) {
            bState = false;
            sText = s;
            bUseValue = bu;
            fValue = f;
            fMin = min;
            fMax = max;
            fIncrement = inc;
        }

        bool bState;
        LPCSTR sText;

        bool bUseValue = false;
        float fValue; float fMin; float fMax; float fIncrement;
    };
    inline std::vector<MenuStruct> Menu;
    inline bool bMenu = false; inline int MenuControl = 1;

    void InitMenu();
    void DrawMenu(IDirect3DDevice9* pDevice);
}

#endif // !MENU

