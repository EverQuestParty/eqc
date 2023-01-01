#include "../common/log.h"
#include "../common/string_util.h"

#include "patch_manager.h"
#define EQC_EXTERN
#include "patch_sod_hooks.h"

int __fastcall SoDGameRegisterZoneHook(void *self, void* unk, int expansion, int zone_id, char *short_name, char *long_name, int string_id, int flag, int g, int h, int i) {
	auto patch = PatchManager::Get().GetPatch();
	return patch->OnRegisterZone(SoDGame__RegisterZone, 479, self, expansion, zone_id, short_name, long_name, string_id, flag, g, h, i);
}

void __fastcall SoDGameRegisterModelHook(void *self, void* unk, int race_id, int gender, const char *name, int unk1, int unk2) {
	auto patch = PatchManager::Get().GetPatch();
	patch->OnRegisterModel(SoDGame__RegisterModel, self, race_id, gender, name, unk1, unk2);
}

int __stdcall SoDGameOnMsgRecvHook(void *self, const char *data, int sz) {
	auto patch = PatchManager::Get().GetPatch();
	return patch->OnMsgRecv(SoDGame__OnMsgRecv, self, data, sz);
}

int __fastcall SoDGameDisplayLoadingMessageHook(void *self, void *unk, int count, const char *msg) {
	auto patch = PatchManager::Get().GetPatch();
	return patch->OnLoadingMessage(SoDGame__DisplayLoadingMessage, SoD_aGame__LoadingMessageArray, 69, self, count, msg);
}

int __fastcall SoDPlayerCommandHandlerHook(void *self, void *unk, DWORD pp, const char *command) {
	auto patch = PatchManager::Get().GetPatch();
	return patch->OnCommand(SoDPlayer__CommandHandler, self, pp, command);
}

void __fastcall SoDPlayerEnterZoneHook(void *self, void* unk, HWND *hwnd) {
	auto patch = PatchManager::Get().GetPatch();
	patch->OnEnterZone(SoDPlayer__EnterZone, self, hwnd);
}
