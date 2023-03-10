#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <SDKDDKVer.h>
#include <detours.h>

#include "../common/log.h"
#include "../common/string_util.h"
#include "../common/safe_write.h"

#include "patch_uf.h"
#include "patch_uf_hooks.h"

uchar UFTrade1[] = {
	0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 
	0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 
	0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 
	0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 
	0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 
	0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 
	0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 
	0x90
};

uchar UFTradeUndo1[] = {
	0x83, 0xB8, 0xD0, 0x00, 0x00, 0x00, 0x01, 0x7E, 
	0x30, 0x8B, 0x0D, 0xE4, 0x83, 0xA9, 0x00, 0x6A, 
	0x01, 0x6A, 0x01, 0x6A, 0x0D, 0x6A, 0x00, 0x68, 
	0x19, 0x02, 0x00, 0x00, 0xE8, 0xD4, 0x0A, 0x0C, 
	0x00, 0x8B, 0x0D, 0x88, 0x6E, 0xB1, 0x00, 0x50, 
	0xE8, 0x88, 0x4D, 0xEF, 0xFF, 0x5F, 0x5E, 0x5D, 
	0x33, 0xC0, 0x5B, 0x83, 0xC4, 0x14, 0xC2, 0x10, 
	0x00
};

uchar UFTrade2[] = {
	0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 
	0x90
};

uchar UFTradeUndo2[] = {
	0x83, 0xBA, 0xD0, 0x00, 0x00, 0x00, 0x01, 0x7F, 
	0x2F
};

void PatchUF::Register() {
	Log::Get().Write(Log::Status, "Registering patch UF");
#ifdef EQC_ENABLE_COMMANDS
	DetourAttach(&(PVOID&)UFPlayer__CommandHandler, UFPlayerCommandHandlerHook);
#endif

	DetourAttach(&(PVOID&)UFGame__RegisterZone, UFGameRegisterZoneHook);
	DetourAttach(&(PVOID&)UFGame__RegisterModel, UFGameRegisterModelHook);
	DetourAttach(&(PVOID&)UFGame__OnMsgRecv, UFGameOnMsgRecvHook);

	SafeWriteBuffer(UF_aGame__TradeStackCheck1, &UFTrade1[0], 57);
	SafeWriteBuffer(UF_aGame__TradeStackCheck2, &UFTrade2[0], 9);
	DetourAttach(&(PVOID&)UFGame__DisplayLoadingMessage, UFGameDisplayLoadingMessageHook);
}

void PatchUF::Unregister() {
	Log::Get().Write(Log::Status, "Unregistering patch UF");
#ifdef EQC_ENABLE_COMMANDS
	DetourDetach(&(PVOID&)UFPlayer__CommandHandler, UFPlayerCommandHandlerHook);
#endif
	DetourDetach(&(PVOID&)UFGame__RegisterZone, UFGameRegisterZoneHook);
	DetourDetach(&(PVOID&)UFGame__RegisterModel, UFGameRegisterModelHook);
	DetourDetach(&(PVOID&)UFGame__OnMsgRecv, UFGameOnMsgRecvHook);

	SafeWriteBuffer(UF_aGame__TradeStackCheck1, &UFTradeUndo1[0], 57);
	SafeWriteBuffer(UF_aGame__TradeStackCheck2, &UFTradeUndo2[0], 9);

	DetourDetach(&(PVOID&)UFGame__DisplayLoadingMessage, UFGameDisplayLoadingMessageHook);
}

void PatchUF::DisplayChat(int color, std::string msg) {
	UFGame__DisplayChat(msg.c_str(), color, true, true);
}
