#ifndef EQC_SRC_PATCH_Titanium_HOOKS_H
#define EQC_SRC_PATCH_Titanium_HOOKS_H

#include "patch_titanium_eqgame.h"

//Game 
int __fastcall TitaniumGameRegisterZoneHook(void *self, void* unk, int expansion, int zone_id, char *short_name, char *long_name, int string_id, int flag, int g, int h, int i);
void __fastcall TitaniumGameRegisterModelHook(void *self, void* unk, int race_id, int gender, const char *name, int unk1, int unk2);
int __stdcall TitaniumGameOnMsgRecvHook(void *self, const char *data, int sz);
int __fastcall TitaniumGameDisplayLoadingMessageHook(void *self, void *unk, int count, const char *msg);

//Player
void __fastcall TitaniumPlayerEnterZoneHook(void *self, void* unk, HWND *hwnd);
int __fastcall TitaniumPlayerCommandHandlerHook(void* self, void *unk, DWORD pp, const char *command);

#endif
