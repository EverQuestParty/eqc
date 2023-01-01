#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <SDKDDKVer.h>
#include <detours.h>

#include "../common/log.h"
#include "../common/string_util.h"

#include "patch_sod.h"
#include "patch_sod_hooks.h"
#include "../common/safe_write.h"

uchar SoDTrade1[] = {
	0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 
	0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 
	0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 
	0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 
	0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 
	0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90
};

uchar SoDTradeUndo1[] = {
	0x7E, 0x2E, 0x8B, 0x0D, 0x9C, 0x25, 0xA4, 0x00, 
	0x6A, 0x01, 0x6A, 0x0D, 0x6A, 0x00, 0x68, 0x19, 
	0x02, 0x00, 0x00, 0xE8, 0xE6, 0xC8, 0x0A, 0x00, 
	0x8B, 0x0D, 0xB8, 0x6D, 0xAD, 0x00, 0x50, 0xE8, 
	0xCA, 0xD1, 0xF0, 0xFF, 0x5F, 0x5E, 0x5D, 0x33, 
	0xC0, 0x5B, 0x83, 0xC4, 0x14, 0xC2, 0x10, 0x00

};

uchar SoDTrade2[] = {
	0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 
	0x90
};

uchar SoDTradeUndo2[] = {
	0x83, 0xBA, 0xD0, 0x00, 0x00, 0x00, 0x01, 0x7F, 
	0x2F
};

void PatchSoD::Register() {
	Log::Get().Write(Log::Status, "Registering patch SoD");
#ifdef EQC_ENABLE_COMMANDS
	DetourAttach(&(PVOID&)SoDPlayer__CommandHandler, SoDPlayerCommandHandlerHook);
#endif

	DetourAttach(&(PVOID&)SoDGame__RegisterZone, SoDGameRegisterZoneHook);
	DetourAttach(&(PVOID&)SoDGame__RegisterModel, SoDGameRegisterModelHook);
	DetourAttach(&(PVOID&)SoDGame__OnMsgRecv, SoDGameOnMsgRecvHook);

	SafeWriteBuffer(SoD_aGame__TradeStackCheck1, &SoDTrade1[0], 48);
	SafeWriteBuffer(SoD_aGame__TradeStackCheck2, &SoDTrade2[0], 9);

	DetourAttach(&(PVOID&)SoDGame__DisplayLoadingMessage, SoDGameDisplayLoadingMessageHook);
}

void PatchSoD::Unregister() {
	Log::Get().Write(Log::Status, "Unregistering patch SoD");
#ifdef EQC_ENABLE_COMMANDS
	DetourDetach(&(PVOID&)SoDPlayer__CommandHandler, SoDPlayerCommandHandlerHook);
#endif

	DetourDetach(&(PVOID&)SoDGame__RegisterZone, SoDGameRegisterZoneHook);
	DetourDetach(&(PVOID&)SoDGame__RegisterModel, SoDGameRegisterModelHook);
	DetourDetach(&(PVOID&)SoDGame__OnMsgRecv, SoDGameOnMsgRecvHook);

	SafeWriteBuffer(SoD_aGame__TradeStackCheck1, &SoDTradeUndo1[0], 48);
	SafeWriteBuffer(SoD_aGame__TradeStackCheck2, &SoDTradeUndo2[0], 9);

	DetourDetach(&(PVOID&)SoDGame__DisplayLoadingMessage, SoDGameDisplayLoadingMessageHook);
}

void PatchSoD::DisplayChat(int color, std::string msg) {
	SoDGame__DisplayChat(msg.c_str(), color, true, true);
}
