#ifndef EQC_SRC_PATCH_ROF2_H
#define EQC_SRC_PATCH_ROF2_H

#include "patch.h"

class PatchRoF2 : public Patch
{
public:
	PatchRoF2() { }
	virtual ~PatchRoF2() { }
	
	virtual void Register();
	virtual void Unregister();

	virtual void DisplayChat(int color, std::string msg);
};

#endif
