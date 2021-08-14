#include "Rendering.h"

void Render::Line(float x1, float y1, float x2, float y2, float width, bool antialias, DWORD color, IDirect3DDevice9* pDevice)
{
    ID3DXLine* m_Line;

    D3DXCreateLine(pDevice, &m_Line);
    D3DXVECTOR2 line[] = { D3DXVECTOR2(x1, y1), D3DXVECTOR2(x2, y2) };
    m_Line->SetWidth(width);
    if (antialias) m_Line->SetAntialias(1);
    m_Line->Begin();
    m_Line->Draw(line, 2, color);
    m_Line->End();
    m_Line->Release();
}
void Render::CText(LPCSTR text, float x, float y, int color)
{
    RECT rect;

    SetRect(&rect, x - 1, y, x - 1, y);
    font->DrawTextA(NULL, text, -1, &rect, DT_CENTER | DT_NOCLIP, D3DCOLOR_ARGB(255, 0, 0, 0));
    SetRect(&rect, x + 1, y, x + 1, y);
    font->DrawTextA(NULL, text, -1, &rect, DT_CENTER | DT_NOCLIP, D3DCOLOR_ARGB(255, 0, 0, 0));
    SetRect(&rect, x, y - 1, x, y - 1);
    font->DrawTextA(NULL, text, -1, &rect, DT_CENTER | DT_NOCLIP, D3DCOLOR_ARGB(255, 0, 0, 0));
    SetRect(&rect, x, y + 1, x, y + 1);
    font->DrawTextA(NULL, text, -1, &rect, DT_CENTER | DT_NOCLIP, D3DCOLOR_ARGB(255, 0, 0, 0));

    SetRect(&rect, x, y, x, y);
    switch (color) {
    case 1:
        font->DrawTextA(NULL, text, -1, &rect, DT_CENTER | DT_NOCLIP, D3DCOLOR_ARGB(255, 0, 255, 0));
        break;

    case 2:
        font->DrawTextA(NULL, text, -1, &rect, DT_CENTER | DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 0, 0));
        break;

    case 3:
        font->DrawTextA(NULL, text, -1, &rect, DT_CENTER | DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 255));
        break;
    case 4:
        font->DrawTextA(NULL, text, -1, &rect, DT_CENTER | DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 255));
        break;
    }

}