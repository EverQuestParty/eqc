#ifndef EQC_COMMON_DATA_FILE_H
#define EQC_COMMON_DATA_FILE_H

#include <string>
#include <vector>
#include "string_util.h"

class EQDataFile
{
public:
	EQDataFile();
	~EQDataFile();
	
	bool Load(const std::string &filename);
	std::vector<std::string> Get(size_t i);
	size_t Size() { return data_.size(); }
private:
	std::vector<std::string> data_;
};

#endif
