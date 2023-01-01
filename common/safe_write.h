#ifndef EQC_COMMON_SAFE_WRITE_H
#define EQC_COMMON_SAFE_WRITE_H

void SafeWrite8(uint32_t addr, uint8_t data);
void SafeWrite16(uint32_t addr, uint16_t data);
void SafeWrite32(uint32_t addr, uint32_t data);
void SafeWrite64(uint32_t addr, uint64_t data);
void SafeWriteBuffer(uint32_t addr, void *data, uint32_t length);

void SafeWriteJump(uint32_t src, uint32_t tgt);
void SafeWriteCall(uint32_t src, uint32_t tgt);
void SafeWriteJnz(uint32_t src, uint32_t tgt);
void SafeWriteJle(uint32_t src, uint32_t tgt);

#endif
