#ifndef EQC_SRC_PATCH_TITANIUM_H
#define EQC_SRC_PATCH_TITANIUM_H

#include "patch.h"

class PatchTitanium : public Patch
{
public:
	PatchTitanium() { }
	virtual ~PatchTitanium() { }
	
	virtual void Register();
	virtual void Unregister();

	virtual void DisplayChat(int color, std::string msg);
};

#endif
