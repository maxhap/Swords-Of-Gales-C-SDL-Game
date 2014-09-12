#ifndef _GREENRUPEE_
#define _GREENRUPEE_

#include "stdafx.h"

class GreenRupee : public Item
{

public:

	GreenRupee( int objectID, int x, int y, int width, int height, string spriteLocation );
	~GreenRupee();

	bool Aquire();

private:

	
};

#endif