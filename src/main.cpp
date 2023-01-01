#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <SDKDDKVer.h>
#include <detours.h>
#include <stdint.h>
#include <cstdio>
#include <string>
#include <bcrypt.h>
#include <SubAuth.h>

#include "patch_manager.h"

HMODULE orig_dll = nullptr;
//DWORD base_address = (DWORD)GetModuleHandle(NULL);
//#define INITIALIZE_EQGAME_OFFSET(var) DWORD var = (((DWORD)var##_x - 0x400000) + baseAddress)

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH: {
		DisableThreadLibraryCalls(hModule);

		DetourTransactionBegin();

		PatchManager::Get().LoadPatch();
		PatchManager::Get().RegisterPatch();

		DetourTransactionCommit();
		break;
	}
	case DLL_PROCESS_DETACH: {
		DetourTransactionBegin();
		DetourUpdateThread(GetCurrentThread());

		PatchManager::Get().UnregisterPatch();
		PatchManager::Get().UnloadPatch();

		DetourTransactionCommit();
		break;
	}
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
		break;
	}
	return TRUE;
}

void LoadOriginalDll(void)
{	
	char buffer[MAX_PATH];
    
    // Getting path to system dir and to dinput.dll
	::GetSystemDirectory(buffer,MAX_PATH);

	// Append dll name
	strcat(buffer, "\\dinput8.dll");
	
	// try to load the system's dinput.dll, if pointer empty
	if (!orig_dll) 
		orig_dll = ::LoadLibrary(buffer);

	// Debug
	if (!orig_dll)
	{
		::ExitProcess(0); // exit the hard way
	}
}

HRESULT WINAPI DirectInput8Create(HINSTANCE hinst, DWORD dwVersion, REFIID riidltf, LPVOID *ppvOut, DWORD punkOuter)
{
	
	if (!orig_dll) 
		LoadOriginalDll(); // looking for the "right dinput.dll"
	
	typedef HRESULT (WINAPI* DirectInputCreateType)(HINSTANCE, DWORD, REFIID, LPVOID*, DWORD);
	DirectInputCreateType DirectInputCreate_fn = (DirectInputCreateType) GetProcAddress(orig_dll, "DirectInput8Create");
    
	HRESULT hr = DirectInputCreate_fn(hinst, dwVersion, riidltf, ppvOut, punkOuter);
	
	// Create my IDirectInput object and store pointer to original object there.
	// note: the object will delete itself once Ref count is zero (similar to COM objects)
	return(hr);
}
