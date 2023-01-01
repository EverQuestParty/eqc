#include <iomanip>
#include <sstream>
#include "types.h"
#include "log.h"
#include "string_util.h"
#include "memory_dump.h"

void MemoryDump(const char *data, size_t size) {
	std::stringstream ss;
	if(size == 0 || size > 39565)
		return;
	// Output as HEX
	char output[4];
	int j = 0;
	char ascii[17];
	memset(ascii, 0, 17);
	uint32 i;
	for(i = 0; i < size; i++)
	{
		if(i % 16 == 0) {
			if(i != 0) {
				ss << " | " << ascii << std::endl;
			}
			ss << std::setw(4) << std::setfill(' ') << i << ": ";
			memset(ascii, 0, 17);
			j = 0;
		}
		else if(i % 8 == 0) {
			ss << "- ";
		}
		sprintf(output, "%02X ", (unsigned char)data[i]);
		ss << output;

		if(data[i] >= 32 && data[i] < 127) {
			ascii[j++] = data[i];
		}
		else {
			ascii[j++] = '.';
		}
	}
	uint32 k = (i - 1) % 16;
	if(k < 8)
		ss << "  ";
	for(uint32 h = k + 1; h < 16; h++) {
		ss << "   ";
	}
	ss << " | " << ascii << std::endl;
	Log::Get().Write(Log::Debug, StringFormat("Memory Dump:\n%s", ss.str().c_str()));
}