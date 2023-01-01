#include "../common/eq_data_file.h"
#include "../common/log.h"
#include "../common/string_util.h"
#include "patch.h"

void Patch::LoadZoneData() {
	zone_data_.clear();

	EQDataFile data;
	if(data.Load("Resources/ZoneData.txt")) {
		size_t sz = data.Size();
		for(size_t i = 0; i < sz; ++i) {
			auto row = data.Get(i);

			if(row.size() >= 9) {
				ZoneDataEntry zde;
				int zone_id = atoi(row[1].c_str());
				zde.expansion = atoi(row[0].c_str());
				zde.short_name = row[2];
				zde.long_name = row[3];
				zde.string_id = atoi(row[4].c_str());
				zde.flag = atoi(row[5].c_str());
				zde.g = atoi(row[6].c_str());
				zde.h = atoi(row[7].c_str());
				zde.i = atoi(row[8].c_str());

				zone_data_[zone_id] = zde;
			}
		}
	}
}

int Patch::OnRegisterZone(pGame__RegisterZone reg, int max_zone_id, void *self, int expansion, int zone_id, char *short_name, char *long_name, int string_id, int flag, int g, int h, int i) {
	Log::Get().Write(Log::Debug, StringFormat("%i^%i^%s^%s^%i^%i^%i^%i^%i", expansion, zone_id, short_name, long_name, string_id, flag, g, h, i));

	if(zone_id == 1) {
		//load zone data
		Log::Get().Write(Log::Debug, StringFormat("Loading zone data..."));
		LoadZoneData();
	}

	if(zone_id == max_zone_id) {
		auto iter = zone_data_.find(zone_id);
		int ret = 0;

		if(iter != zone_data_.end()) {
			auto zde = iter->second;
			zone_data_.erase(iter);

			ret = reg(self, zde.expansion, zone_id, zde.short_name.c_str(), zde.long_name.c_str(), zde.string_id, zde.flag, zde.g, zde.h, zde.i);
		}
		else {
			ret = reg(self, expansion, zone_id, short_name, long_name, string_id, flag, g, h, i);
		}

		iter = zone_data_.begin();
		while(iter != zone_data_.end()) {
			auto zid = iter->first;
			auto zde = iter->second;

			iter = zone_data_.erase(iter);
			reg(self, zde.expansion, zid, zde.short_name.c_str(), zde.long_name.c_str(), zde.string_id, zde.flag, zde.g, zde.h, zde.i);
		}

		return ret;
	}
	else {
		auto iter = zone_data_.find(zone_id);

		if(iter != zone_data_.end()) {
			auto zde = iter->second;
			zone_data_.erase(iter);

			return reg(self, zde.expansion, zone_id, zde.short_name.c_str(), zde.long_name.c_str(), zde.string_id, zde.flag, zde.g, zde.h, zde.i);
		}
		else {
			return reg(self, expansion, zone_id, short_name, long_name, string_id, flag, g, h, i);
		}
	}

	return reg(self, expansion, zone_id, short_name, long_name, string_id, flag, g, h, i);
}

int Patch::OnRegisterZoneNew(pGame__RegisterZone reg, void *self, int expansion, int zone_id, char *short_name, char *long_name, int string_id, int flag, int g, int h, int i) {
	Log::Get().Write(Log::Debug, StringFormat("%i^%i^%s^%s^%i^%i^%i^%i^%i", expansion, zone_id, short_name, long_name, string_id, flag, g, h, i));
	
	if(zone_id == 1) {
		//load zone data
		Log::Get().Write(Log::Debug, StringFormat("Loading zone data..."));
		LoadZoneData();
	}
	
	auto iter = zone_data_.find(zone_id);
	
	if(iter != zone_data_.end()) {
		auto zde = iter->second;
		zone_data_.erase(iter);
	
		return reg(self, zde.expansion, zone_id, zde.short_name.c_str(), zde.long_name.c_str(), zde.string_id, zde.flag, zde.g, zde.h, zde.i);
	} else {
		return reg(self, expansion, zone_id, short_name, long_name, string_id, flag, g, h, i);
	}
}

int Patch::OnRegisterZoneNew2(pGame__RegisterZone2 reg, int max_zone_id, void *self, int expansion, int zone_id, char *short_name, char *long_name, int string_id, int flag, int g, int h, int i) {
	if(zone_id == max_zone_id) {
		int ret = reg(self, expansion, zone_id, short_name, long_name, string_id, flag, g, h, i);
	
		auto iter = zone_data_.begin();
		while(iter != zone_data_.end()) {
			auto zid = iter->first;
			auto zde = iter->second;
	
			iter = zone_data_.erase(iter);
			reg(self, zde.expansion, zid, zde.short_name.c_str(), zde.long_name.c_str(), zde.string_id, zde.flag, zde.g, zde.h, zde.i);
		}
	
		return ret;
	}
	
	return reg(self, expansion, zone_id, short_name, long_name, string_id, flag, g, h, i);
}
