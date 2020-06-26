// Copyright 2020 jeonghun

#include <windows.h>
#include <dinput.h>
#include "dll_loader.h"
#include "fps_unlock.h"


static dll_loader dinput8(L"dinput8", true);
HRESULT WINAPI DirectInput8Create(HINSTANCE hinst, DWORD dwVersion, REFIID riidltf, LPVOID *ppvOut, LPUNKNOWN punkOuter) {
  return dinput8.call<decltype(&DirectInput8Create)>("DirectInput8Create", hinst, dwVersion, riidltf, ppvOut, punkOuter);
}


int APIENTRY DllMain(HMODULE hDLL, DWORD Reason, LPVOID Reserved) {
  switch (Reason) {
  case DLL_PROCESS_ATTACH:
    DisableThreadLibraryCalls(hDLL);
    fps_unlock::apply();
    break;

  case DLL_PROCESS_DETACH:
    break;
  }

  return TRUE;
}
