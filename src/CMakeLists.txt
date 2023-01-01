CMAKE_MINIMUM_REQUIRED(VERSION 3.12)

SET(mod_sources
	dinput8.def
	main.cpp
	patch.cpp
	patch_command.cpp
	patch_manager.cpp
	patch_null.cpp
	patch_rof2.cpp
	patch_rof2_hooks.cpp
	patch_sod.cpp
	patch_sod_hooks.cpp
	patch_titanium.cpp
	patch_titanium_hooks.cpp
	patch_uf.cpp
	patch_uf_hooks.cpp
	patch_zone.cpp
)

SET(mod_headers
	command_data.h
	eqgame_functions.h
	patch.h
	patch_manager.h
	patch_null.h
	patch_rof2.h
	patch_rof2_eqgame.h
	patch_rof2_hooks.h
	patch_sod.h
	patch_sod_eqgame.h
	patch_sod_hooks.h
	patch_titanium.h
	patch_titanium_eqgame.h
	patch_titanium_hooks.h
	patch_uf.h
	patch_uf_eqgame.h
	patch_uf_hooks.h
	zone_data.h
)

INCLUDE_DIRECTORIES("${DETOURS_INCLUDE_DIR}")

ADD_LIBRARY(dinput8 SHARED ${mod_sources} ${mod_headers})
TARGET_LINK_LIBRARIES(dinput8 common ${DETOURS_LIBRARIES})
INSTALL(TARGETS dinput8 RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX})

SET(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
