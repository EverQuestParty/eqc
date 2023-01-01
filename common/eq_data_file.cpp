#include "eq_data_file.h"
#include <stdio.h>

EQDataFile::EQDataFile() {
}

EQDataFile::~EQDataFile() {
}

bool EQDataFile::Load(const std::string &filename) {
	data_.clear();

	FILE *f = fopen(filename.c_str(), "r");
	if(!f) {
		return false;
	}

	char line[1024] = { 0 };
	while(fgets(line, 1024, f)) {
		data_.push_back(line);
	}

	fclose(f);
	return true;
}

std::vector<std::string> EQDataFile::Get(size_t i) {
	if(i >= data_.size()) {
		return std::vector<std::string>();
	}

	return SplitString(data_[i], '^');
}
