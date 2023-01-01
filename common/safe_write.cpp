#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <SDKDDKVer.h>
#include <stdint.h>
#include "safe_write.h"

void SafeWrite8(uint32_t addr, uint8_t data) {
	SafeWriteBuffer(addr, &data, 1);
}

void SafeWrite16(uint32_t addr, uint16_t data) {
	SafeWriteBuffer(addr, &data, 2);
}

void SafeWrite32(uint32_t addr, uint32_t data) {
	SafeWriteBuffer(addr, &data, 4);
}

void SafeWrite64(uint32_t addr, uint64_t data) {
	SafeWriteBuffer(addr, &data, 8);
}

void SafeWriteBuffer(uint32_t addr, void *data, uint32_t length) {
	DWORD old_protect;
	VirtualProtect((void*)addr, length, PAGE_EXECUTE_READWRITE, &old_protect);
	memcpy((void*)addr, data, length);
	VirtualProtect((void*)addr, length, old_protect, &old_protect);
}

void SafeWriteJump(uint32_t src, uint32_t tgt) {
	SafeWrite8(src, 0xE9);
	SafeWrite32(src + 1, tgt - src - 1 - 4);
}

void SafeWriteCall(uint32_t src, uint32_t tgt) {
	SafeWrite8(src, 0xE8);
	SafeWrite32(src + 1, tgt - src - 1 - 4);
}

void SafeWriteJnz(uint32_t src, uint32_t tgt) {
	SafeWrite16(src, 0x850F);
	SafeWrite32(src + 2, tgt - src - 2 - 4);
}

void SafeWriteJle(uint32_t src, uint32_t tgt) {
	SafeWrite16(src, 0x8E0F);
	SafeWrite32(src + 2, tgt - src - 2 - 4);
}
