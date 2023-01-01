#ifndef EQC_SRC_PATCH_SOD_H
#define EQC_SRC_PATCH_SOD_H

#include "patch.h"

class PatchSoD : public Patch
{
public:
	PatchSoD() { }
	virtual ~PatchSoD() { }
	
	virtual void Register();
	virtual void Unregister();

	virtual void DisplayChat(int color, std::string msg);
};

#endif
