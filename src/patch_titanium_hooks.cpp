#include "../common/log.h"
#include "../common/string_util.h"

#include "patch_manager.h"
#define EQC_EXTERN
#include "patch_titanium_hooks.h"

int __fastcall TitaniumGameRegisterZoneHook(void *self, void* unk, int expansion, int zone_id, char *short_name, char *long_name, int string_id, int flag, int g, int h, int i) {
	auto patch = PatchManager::Get().GetPatch();
	return patch->OnRegisterZone(TitaniumGame__RegisterZone, 368, self, expansion, zone_id, short_name, long_name, string_id, flag, g, h, i);
}

void __fastcall TitaniumGameRegisterModelHook(void *self, void* unk, int race_id, int gender, const char *name, int unk1, int unk2) {
	auto patch = PatchManager::Get().GetPatch();
	patch->OnRegisterModel(TitaniumGame__RegisterModel, self, race_id, gender, name, unk1, unk2);
}

int __stdcall TitaniumGameOnMsgRecvHook(void *self, const char *data, int sz) {
	auto patch = PatchManager::Get().GetPatch();
	return patch->OnMsgRecv(TitaniumGame__OnMsgRecv, self, data, sz);
}

int __fastcall TitaniumGameDisplayLoadingMessageHook(void *self, void *unk, int count, const char *msg) {
	auto patch = PatchManager::Get().GetPatch();
	return patch->OnLoadingMessage(TitaniumGame__DisplayLoadingMessage, Titanium_aGame__LoadingMessageArray, 68, self, count, msg);
}

int __fastcall TitaniumPlayerCommandHandlerHook(void *self, void *unk, DWORD pp, const char *command) {
	auto patch = PatchManager::Get().GetPatch();
	return patch->OnCommand(TitaniumPlayer__CommandHandler, self, pp, command);
}

void __fastcall TitaniumPlayerEnterZoneHook(void *self, void* unk, HWND *hwnd) {
	auto patch = PatchManager::Get().GetPatch();
	patch->OnEnterZone(TitaniumPlayer__EnterZone, self, hwnd);
}
