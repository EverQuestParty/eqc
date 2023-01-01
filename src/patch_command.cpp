#include "../common/eq_data_file.h"
#include "../common/log.h"
#include "../common/string_util.h"
#include "patch.h"

void Patch::LoadCommandData() {
	command_aliases_.clear();
	command_list_.clear();
	EQDataFile alias;
	EQDataFile custom;

	if(alias.Load("Resources/CommandAlias.txt")) {
		size_t sz = alias.Size();
		for(size_t i = 0; i < sz; ++i) {
			auto row = alias.Get(i);

			if(row.size() >= 2) {
				CommandAliasEntry cae;
				cae.command = ToLowerString(row[0]);
				cae.replacement = ToLowerString(row[1]);

				command_aliases_[cae.command] = cae;
			}
		}
	}

	if(custom.Load("Resources/Commands.txt")) {
		size_t sz = custom.Size();
		for(size_t i = 0; i < sz; ++i) {
			auto row = custom.Get(i);

			if(row.size() >= 3) {
				CommandEntry cce;
				cce.command = ToLowerString(row[0]);
				cce.type = atoi(row[1].c_str());
				cce.custom = atoi(row[2].c_str()) ? true : false;

				command_list_.push_back(cce);
			}
		}
	}

	command_data_loaded_ = true;
}

int Patch::OnCommand(pPlayer__CommandHandler ch, void *self, DWORD pp, const char *command) {
	if(!command_data_loaded_)
		LoadCommandData();

	std::string cmd;
	auto args = SplitString(command, ' ');

	if(args.size() == 0) {
		return 0;
	}

	cmd = ToLowerString(args[0]);
	args.erase(args.begin());

	//Apply alias if applicable
	std::string command_str = command;
	auto alias_entry = command_aliases_.find(cmd);
	if(alias_entry != command_aliases_.end())
	{
		Log::Get().Write(Log::Debug, StringFormat("Alias found for command: '%s'", alias_entry->second.replacement.c_str()));
		command_str.replace(0, cmd.length(), alias_entry->second.replacement);
	}

	if(command_list_.size() == 0) {
		return ch(self, pp, command_str.c_str());
	}

	auto command_entry = command_list_.begin();
	while(command_entry != command_list_.end()) {
		if(command_entry->command.compare(cmd) == 0) {
			break;
		}
		++command_entry;
	}

	if(command_entry == command_list_.end()) {
		return ch(self, pp, command_str.c_str());
	}

	if(cmd.compare("/help") == 0) {
		if(args.size() == 1) {
			std::string arg = ToLowerString(args[0]);
			int list_type = 0;
			if(arg.compare("normal") == 0) {
				list_type = 1;
			}
			else if(arg.compare("emote") == 0) {
				list_type = 2;
			}
			else if(arg.compare("guild") == 0) {
				list_type = 3;
			}
			else if(arg.compare("voice") == 0) {
				list_type = 4;
			}
			else if(arg.compare("chat") == 0) {
				list_type = 5;
			} 
			else {
				DisplayChat(273, "Format: / help <class> Where class is one of normal, emote, or guild");
				DisplayChat(273, "Normal will display a list of all commands.");
				DisplayChat(273, "Emote will display a list of all player emotes.");
				DisplayChat(273, "Guild will display a list of guild commands.");
				DisplayChat(273, "Voice will display a list of voice control commands.");
				DisplayChat(273, "Chat will display a list of chat channel commands.");
				return 0;
			}

			if(list_type >= 1 && list_type <= 5) {
				DisplayChat(273, "List of commands");
				DisplayChat(273, "--------------------------------------------------------------------------------");
				for(auto &command_entry : command_list_) {
					if(command_entry.type == list_type) {
						DisplayChat(273, command_entry.command);
					}
				}
			}

			return 0;
		} else {
			DisplayChat(273, "Format: / help <class> Where class is one of normal, emote, or guild");
			DisplayChat(273, "Normal will display a list of all commands.");
			DisplayChat(273, "Emote will display a list of all player emotes.");
			DisplayChat(273, "Guild will display a list of guild commands.");
			DisplayChat(273, "Voice will display a list of voice control commands.");
			DisplayChat(273, "Chat will display a list of chat channel commands.");
			return 0;
		}
	}

	if(command_entry->custom) {
		SendReliableMessage(0x14FF, command_str.c_str(), command_str.length() + 1);
		return 0;
	}

	return ch(self, pp, command_str.c_str());
}

