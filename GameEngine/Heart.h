#ifndef _HEART_
#define _HEART_

#include "stdafx.h"

class Heart : public Item
{

public:

	Heart( int objectID, int x, int y, int width, int height, string spriteLocation );
	~Heart();

	bool Aquire();

private:

	
};

#endif