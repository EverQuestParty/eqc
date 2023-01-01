#ifndef EQC_SRC_PATCH_ROF2_HOOKS_H
#define EQC_SRC_PATCH_ROF2_HOOKS_H

#include "patch_rof2_eqgame.h"

//Game
int __fastcall RoF2GameRegisterZoneHook(void *self, void* unk, int expansion, int zone_id, char *short_name, char *long_name, int string_id, int flag, int g, int h, int i);
int __fastcall RoF2GameRegisterZone2Hook(void *self, void* unk, int expansion, int zone_id, char *short_name, char *long_name, int string_id, int flag, int g, int h, int i);
void __fastcall RoF2GameRegisterModelHook(void *self, void* unk, int race_id, int gender, const char *name, int unk1, int unk2);
int __stdcall RoF2GameOnMsgRecvHook(void *self, const char *data, int sz);
int __fastcall RoF2GameDisplayLoadingMessageHook(void *self, void *unk, int count, const char *msg);

//Player
void __fastcall RoF2PlayerEnterZoneHook(void *self, void* unk, HWND *hwnd);
int __fastcall RoF2PlayerCommandHandlerHook(void* self, void *unk, DWORD pp, const char *command);

#endif
