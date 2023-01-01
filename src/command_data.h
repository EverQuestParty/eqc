#ifndef EQC_SRC_COMMAND_DATA_H
#define EQC_SRC_COMMAND_DATA_H

#include <string>

struct CommandAliasEntry
{
	std::string command;
	std::string replacement;
};

struct CommandEntry
{
	std::string command;
	int type;
	bool custom;
};

#endif
