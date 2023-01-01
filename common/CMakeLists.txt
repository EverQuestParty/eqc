CMAKE_MINIMUM_REQUIRED(VERSION 3.12)

SET(common_sources
	crc32.cpp
	eq_data_file.cpp
	file_verify.cpp
	log.cpp
	memory_dump.cpp
	safe_write.cpp
	stack_walker.cpp
	string_util.cpp
)

SET(common_headers
	crc32.h
	eq_data_file.h
	eqemu_structs.h
	file_verify.h
	log.h
	logical_packet.h
	memory_dump.h
	safe_write.h
	stack_walker.h
	string_util.h
	types.h
)

ADD_LIBRARY(common ${common_sources} ${common_headers})
SET(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
