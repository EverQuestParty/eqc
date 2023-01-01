#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <SDKDDKVer.h>
#include <detours.h>

#include "../common/log.h"
#include "../common/string_util.h"
#include "../common/safe_write.h"

#include "patch_titanium.h"
#include "patch_titanium_hooks.h"

uchar TitaniumTrade1[] = {
	0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 
	0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 
	0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 
	0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 
	0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90
};

uchar TitaniumTradeUndo1[] = {
	0x8B, 0x0D, 0xB0, 0x5C, 0x90, 0x00, 0x6A, 0x01, 
	0x6A, 0x0D, 0x6A, 0x00, 0x68, 0x19, 0x02, 0x00, 
	0x00, 0xE8, 0x27, 0x4A, 0x0C, 0x00, 0x8B, 0x0D, 
	0xF0, 0x8D, 0x98, 0x00, 0x50, 0xE8, 0xE1, 0xD2, 
	0xF7, 0xFF, 0xE9, 0x1C, 0xFD, 0xFF, 0xFF
};

uchar TitaniumTrade2[] = {
	0x90, 0x90, 0x90, 0x90, 0x90, 0x90
};

uchar TitaniumTradeUndo2[] = {
	0x83, 0x78, 0x48, 0x01, 0x7F, 0x2B
};

void PatchTitanium::Register() {
	Log::Get().Write(Log::Status, "Registering patch Titanium");
#ifdef EQC_ENABLE_COMMANDS
	DetourAttach(&(PVOID&)TitaniumPlayer__CommandHandler, TitaniumPlayerCommandHandlerHook);
#endif

	DetourAttach(&(PVOID&)TitaniumGame__RegisterZone, TitaniumGameRegisterZoneHook);
	DetourAttach(&(PVOID&)TitaniumGame__RegisterModel, TitaniumGameRegisterModelHook);
	DetourAttach(&(PVOID&)TitaniumGame__OnMsgRecv, TitaniumGameOnMsgRecvHook);

	SafeWriteBuffer(Titanium_aGame__TradeStackCheck1, &TitaniumTrade1[0], 39);
	SafeWriteBuffer(Titanium_aGame__TradeStackCheck2, &TitaniumTrade2[0], 6);

	DetourAttach(&(PVOID&)TitaniumGame__DisplayLoadingMessage, TitaniumGameDisplayLoadingMessageHook);
}

void PatchTitanium::Unregister() {
	Log::Get().Write(Log::Status, "Unregistering patch Titanium");
#ifdef EQC_ENABLE_COMMANDS
	DetourDetach(&(PVOID&)TitaniumPlayer__CommandHandler, TitaniumPlayerCommandHandlerHook);
#endif

	DetourDetach(&(PVOID&)TitaniumGame__RegisterZone, TitaniumGameRegisterZoneHook);
	DetourDetach(&(PVOID&)TitaniumGame__RegisterModel, TitaniumGameRegisterModelHook);
	DetourDetach(&(PVOID&)TitaniumGame__OnMsgRecv, TitaniumGameOnMsgRecvHook);

	SafeWriteBuffer(Titanium_aGame__TradeStackCheck1, &TitaniumTradeUndo1[0], 39);
	SafeWriteBuffer(Titanium_aGame__TradeStackCheck2, &TitaniumTradeUndo2[0], 6);

	DetourDetach(&(PVOID&)TitaniumGame__DisplayLoadingMessage, TitaniumGameDisplayLoadingMessageHook);
}

void PatchTitanium::DisplayChat(int color, std::string msg) {
	TitaniumGame__DisplayChat(msg.c_str(), color, true, true);
}
