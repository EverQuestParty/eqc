#ifndef EQC_SRC_PATCH_UF_H
#define EQC_SRC_PATCH_UF_H

#include "patch.h"

class PatchUF : public Patch
{
public:
	PatchUF() { }
	virtual ~PatchUF() { }
	
	virtual void Register();
	virtual void Unregister();

	virtual void DisplayChat(int color, std::string msg);
};

#endif
