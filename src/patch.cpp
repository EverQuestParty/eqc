#include "../common/eq_data_file.h"
#include "../common/log.h"
#include "../common/string_util.h"
#include "../common/memory_dump.h"
#include "patch.h"

#define MAX_LOADING_MESSAGES 128
#define MAX_LOADING_MESSAGE_LEN 256
char LoadingMessages[MAX_LOADING_MESSAGES][MAX_LOADING_MESSAGE_LEN];

void Patch::OnEnterZone(pPlayer__EnterZone enter, void *self, HWND *hWnd)
{
	enter(self, hWnd);
	Log::Get().Write(Log::Status, "Enter Zone");
}

int Patch::OnMsgRecv(pGame__OnMsgRecv mr, void *self, const char *data, int sz) {
	Log::Get().Write(Log::Debug, StringFormat("[0x%04x, size: %u]", *(uint16*)data, sz - 2));
	MemoryDump(data + 2, sz - 2);
	return mr(self, data, sz);
}

int Patch::OnLoadingMessage(pGame__DisplayLoadingMessage lm, DWORD array_offset, int array_size, void* self, int a, char const *msg) {
	Log::Get().Write(Log::Debug, StringFormat("%p %i %s", self, a, msg ? msg : ""));
	if(!loading_messages_loaded_) {
		memset(LoadingMessages, 0, sizeof(LoadingMessages));

		char **ptr = (char **)array_offset;
		for(int i = 0; i < array_size; ++i) {
			Log::Get().Write(Log::Debug, StringFormat("LM: %s", ptr[i] ? ptr[i] : ""));
		}
	
		EQDataFile data;
		if(data.Load("Resources/LoadingMessages.txt")) {
			size_t sz = data.Size();
	
			if(sz == 0) {
				loading_messages_loaded_ = true;
				return lm(self, a, msg);
			}

			if(sz > MAX_LOADING_MESSAGES) {
				sz = MAX_LOADING_MESSAGES;
			}
	
			for(size_t i = 0; i < sz; ++i) {
				auto row = data.Get(i);
	
				if(row.size() >= 1) {
					strn0cpy(LoadingMessages[i], row[0].c_str(), MAX_LOADING_MESSAGE_LEN);
				}
			}
		} else {
			loading_messages_loaded_ = true;
			return lm(self, a, msg);
		}
	
		if(array_size > MAX_LOADING_MESSAGES) {
			array_size = MAX_LOADING_MESSAGES;
		}
	
		for(int i = 0; i < array_size; ++i) {
			ptr[i] = LoadingMessages[i];
		}
	
		loading_messages_loaded_ = true;
	}

	return lm(self, a, msg);
}

void Patch::OnRegisterModel(pGame__RegisterModel rm, void *self, int race_id, int gender, const char *name, int unk1, int unk2) {
	Log::Get().Write(Log::Debug, StringFormat("%i^%i^%s^%i^%i", race_id, gender, name, unk1, unk2));
	if(!register_models_loaded_) {
		EQDataFile data;
		if(data.Load("Resources/ModelData.txt")) {
			size_t sz = data.Size();

			for(size_t i = 0; i < sz; ++i) {
				auto row = data.Get(i);

				if(row.size() >= 5) {
					rm(self, atoi(row[0].c_str()), atoi(row[1].c_str()), row[2].c_str(), atoi(row[3].c_str()), atoi(row[4].c_str()));
				}
			}

			register_models_bypass_ = true;
		} else {
			register_models_loaded_ = true;
			rm(self, race_id, gender, name, unk1, unk2);
			return;
		}

		register_models_loaded_ = true;
	}

	if(!register_models_bypass_) {
		rm(self, race_id, gender, name, unk1, unk2);
	}
}