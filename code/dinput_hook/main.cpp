/*
This is free and unencumbered software released into the public domain.

Anyone is free to copy, modify, publish, use, compile, sell, or
distribute this software, either in source code form or as a compiled
binary, for any purpose, commercial or non-commercial, and by any
means.

In jurisdictions that recognize copyright laws, the author or authors
of this software dedicate any and all copyright interest in the
software to the public domain. We make this dedication for the benefit
of the public at large and to the detriment of our heirs and
successors. We intend this dedication to be an overt act of
relinquishment in perpetuity of all present and future rights to this
software under copyright law.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.
*/

//IMPORTANT(adm244): SCRATCH VERSION JUST TO GET IT UP WORKING

#include <windows.h>

#define internal static

typedef HRESULT __stdcall DInput8CreateFunc(HINSTANCE, DWORD, REFIID, LPVOID *, LPUNKNOWN);

internal HMODULE obsilver = 0;

extern "C" HRESULT __stdcall FakeDirectInput8Create(
  HINSTANCE hinst,
  DWORD dwVersion,
  REFIID riidltf,
  LPVOID * ppvOut,
  LPUNKNOWN punkOuter
)
{
  HMODULE dinput8 = LoadLibrary("c:\\windows\\system32\\dinput8.dll");
  DInput8CreateFunc *DInput8Create = (DInput8CreateFunc *)GetProcAddress(dinput8, "DirectInput8Create");
  
  return DInput8Create(hinst, dwVersion, riidltf, ppvOut, punkOuter);
}

internal BOOL WINAPI DllMain(HANDLE procHandle, DWORD reason, LPVOID reserved)
{
  if(reason == DLL_PROCESS_ATTACH)
  {
    //MessageBox(NULL, "Hook library is loaded!", "Yey!", MB_OK);
    obsilver = LoadLibrary("obsilver_v2.dll");
  }

  return TRUE;
}
