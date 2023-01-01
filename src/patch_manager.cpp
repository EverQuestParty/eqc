#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <SDKDDKVer.h>
#include <detours.h>
#include <stdio.h>

#include "../common/crc32.h"
#include "../common/log.h"

#include "patch_manager.h"
#include "patch_null.h"
#include "patch_rof2.h"
#include "patch_sod.h"
#include "patch_titanium.h"
#include "patch_uf.h"

void PatchManager::LoadPatch() {
	if(patch_ > 0) {
		return;
	}

	FILE *f = fopen("eqgame.exe", "rb");

	if(!f) {
		patch_ = std::unique_ptr<Patch>(new PatchNull());
		return;
	}

	fseek(f, 0U, SEEK_END);
	auto size = ftell(f);
	rewind(f);

	std::unique_ptr<char> buffer = std::unique_ptr<char>(new char[size]);
	auto result = fread(buffer.get(), 1, size, f);
	fclose(f);

	if(result != size) {
		patch_ = std::unique_ptr<Patch>(new PatchNull());
		return;
	}

	uint32 crc = CRC32::GenerateNoFlip((uchar*)buffer.get(), size);

	Log::Get().Write(Log::Status, "Load patch...");

	switch(crc) {
	case 1655895739: { // SoD
		patch_ = std::unique_ptr<Patch>(new PatchSoD());
		Log::Get().Write(Log::Status, "Patch loaded as SoD");
		break;
	}
	case 1204195887: { // RoF2
		patch_ = std::unique_ptr<Patch>(new PatchRoF2());
		Log::Get().Write(Log::Status, "Patch loaded as RoF2");
		break;
	}
	case 890011777: { // UF
		patch_ = std::unique_ptr<Patch>(new PatchUF());
		Log::Get().Write(Log::Status, "Patch loaded as UF");
		break;
	}
	case 2652224660: { // Titanium
		patch_ = std::unique_ptr<Patch>(new PatchTitanium());
		Log::Get().Write(Log::Status, "Patch loaded as Titanium");
		break;
	}
	default: {
		patch_ = std::unique_ptr<Patch>(new PatchNull());
		Log::Get().Write(Log::Status, "Patch loaded as Null");
		break;
	}
	}
}

void PatchManager::RegisterPatch() {
	if(!patch_) {
		return;
	}

	patch_->Register();
}

void PatchManager::UnloadPatch() {
	patch_ = nullptr;
}

void PatchManager::UnregisterPatch() {
	if(!patch_) {
		return;
	}

	patch_->Unregister();
}

Patch *PatchManager::GetPatch() {
	return patch_.get();
}
