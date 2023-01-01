#ifndef EQC_SRC_PATCH_SOD_HOOKS_H
#define EQC_SRC_PATCH_SOD_HOOKS_H

#include "patch_sod_eqgame.h"

//Game 
int __fastcall SoDGameRegisterZoneHook(void *self, void* unk, int expansion, int zone_id, char *short_name, char *long_name, int string_id, int flag, int g, int h, int i);
void __fastcall SoDGameRegisterModelHook(void *self, void* unk, int race_id, int gender, const char *name, int unk1, int unk2);
int __stdcall SoDGameOnMsgRecvHook(void *self, const char *data, int sz);
int __fastcall SoDGameDisplayLoadingMessageHook(void *self, void *unk, int count, const char *msg);

//Player
void __fastcall SoDPlayerEnterZoneHook(void *self, void* unk, HWND *hwnd);
int __fastcall SoDPlayerCommandHandlerHook(void* self, void *unk, DWORD pp, const char *command);

#endif
