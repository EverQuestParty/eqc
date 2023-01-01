#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <SDKDDKVer.h>
#include <detours.h>

#include "../common/log.h"
#include "../common/string_util.h"

#include "patch_rof2.h"
#include "patch_rof2_hooks.h"

void PatchRoF2::Register() {
	Log::Get().Write(Log::Status, "Registering patch RoF2");
#ifdef EQC_ENABLE_COMMANDS
	DetourAttach(&(PVOID&)RoF2Player__CommandHandler, RoF2PlayerCommandHandlerHook);
#endif

	DetourAttach(&(PVOID&)RoF2Game__RegisterZone, RoF2GameRegisterZoneHook);
	DetourAttach(&(PVOID&)RoF2Game__RegisterZone2, RoF2GameRegisterZone2Hook);
	DetourAttach(&(PVOID&)RoF2Game__RegisterModel, RoF2GameRegisterModelHook);
	DetourAttach(&(PVOID&)RoF2Game__OnMsgRecv, RoF2GameOnMsgRecvHook);
	DetourAttach(&(PVOID&)RoF2Game__DisplayLoadingMessage, RoF2GameDisplayLoadingMessageHook);
}

void PatchRoF2::Unregister() {
	Log::Get().Write(Log::Status, "Unregistering patch RoF2");
#ifdef EQC_ENABLE_COMMANDS
	DetourDetach(&(PVOID&)RoF2Player__CommandHandler, RoF2PlayerCommandHandlerHook);
#endif

	DetourDetach(&(PVOID&)RoF2Game__RegisterZone, RoF2GameRegisterZoneHook);
	DetourDetach(&(PVOID&)RoF2Game__RegisterZone2, RoF2GameRegisterZone2Hook);
	DetourDetach(&(PVOID&)RoF2Game__RegisterModel, RoF2GameRegisterModelHook);
	DetourDetach(&(PVOID&)RoF2Game__OnMsgRecv, RoF2GameOnMsgRecvHook);
	DetourDetach(&(PVOID&)RoF2Game__DisplayLoadingMessage, RoF2GameDisplayLoadingMessageHook);
}

void PatchRoF2::DisplayChat(int color, std::string msg) {
	RoF2Game__DisplayChat(msg.c_str(), color, true, true);
}
