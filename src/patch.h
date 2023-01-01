#ifndef EQC_SRC_PATCH_H
#define EQC_SRC_PATCH_H

#include <Windows.h>
#include <map>
#include <list>

#include "zone_data.h"
#include "command_data.h"
#include "eqgame_functions.h"

class Patch
{
public:
	Patch() { command_data_loaded_ = false; loading_messages_loaded_ = false; register_models_loaded_ = false; register_models_bypass_ = false; }
	virtual ~Patch() { }
	
	virtual void Register() = 0;
	virtual void Unregister() = 0;

	virtual void SendReliableMessage(int message_id, const char *data, size_t data_len) { }
	virtual void DisplayChat(int color, std::string msg) { }

	void OnEnterZone(pPlayer__EnterZone enter, void *self, HWND *hWnd);
	int OnRegisterZone(pGame__RegisterZone reg, int max_zone_id, void *self, int expansion, int zone_id, char *short_name, char *long_name, int string_id, int flag, int g, int h, int i);
	int OnRegisterZoneNew(pGame__RegisterZone reg, void *self, int expansion, int zone_id, char *short_name, char *long_name, int string_id, int flag, int g, int h, int i);
	int OnRegisterZoneNew2(pGame__RegisterZone2 reg, int max_zone_id, void *self, int expansion, int zone_id, char *short_name, char *long_name, int string_id, int flag, int g, int h, int i);
	void OnRegisterModel(pGame__RegisterModel rm, void *self, int race_id, int gender, const char *name, int unk1, int unk2);
	int OnCommand(pPlayer__CommandHandler ch, void *self, DWORD pp, const char *command);
	int OnMsgRecv(pGame__OnMsgRecv mr, void *self, const char *data, int sz);
	int OnLoadingMessage(pGame__DisplayLoadingMessage lm, DWORD array_offset, int array_size, void* self, int a, char const *msg);
protected:
	void LoadZoneData();
	std::map<int, ZoneDataEntry> zone_data_;

	void LoadCommandData();
	std::map<std::string, CommandAliasEntry> command_aliases_;
	std::list<CommandEntry> command_list_;
	bool command_data_loaded_;
	bool loading_messages_loaded_;
	bool register_models_loaded_;
	bool register_models_bypass_;
};

#endif
