#include <iostream>
#include <Windows.h>
#include <chrono>
#include <thread>
#include "Globals.h"
#include "Offsets.h"
#include "Features.h"
#include "Hooks.h"
#include "Menu.h"
#include "Interface.h"


void UnHook(HMODULE hModule) {
    Hooks::Release();
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    FreeLibraryAndExitThread(hModule, 0);
}

DWORD WINAPI ThreadProc(HMODULE hModule) {
    Menu::InitMenu();
    baseModule = (DWORD)GetModuleHandle("client.dll");
    engineModule = (DWORD)GetModuleHandle("engine.dll");

    Interfaces::InitInterface();
    Hooks::InitHooks();

    while (!GetAsyncKeyState(VK_END)) {
        Features::ButtonHandling();
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
    

    UnHook(hModule);

    return 0;
}


BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
    DisableThreadLibraryCalls(hModule);

    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        CloseHandle(CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadProc, hModule, 0, NULL));
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }

    return TRUE;
}

