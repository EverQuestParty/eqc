#ifndef EQC_SRC_ZONE_DATA_H
#define EQC_SRC_ZONE_DATA_H

#include <string>

struct ZoneDataEntry
{
	int expansion;
	std::string short_name;
	std::string long_name;
	int string_id;
	int flag;
	int g;
	int h;
	int i;
};

#endif