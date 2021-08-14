#ifndef RENDER_H
#define RENDER_H
#include <iostream>
#include <Windows.h>

#include <d3d9.h>
#include <d3dx9.h>

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

namespace Render {
    inline LPD3DXFONT font;
    void Line(float x1, float y1, float x2, float y2, float width, bool antialias, DWORD color, IDirect3DDevice9* pDevice);
    void CText(LPCSTR text, float x, float y, int color);
};

#endif // !RENDER_H
