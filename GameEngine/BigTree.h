#ifndef _BIGTREE_
#define _BIGTREE_

#include "stdafx.h"

class BigTree : public GameObject
{

public:

	BigTree( int objectID, int x, int y, int width, int height, int startingAngle, int movementSpeed, string spriteLocation, bool isHittable );
	~BigTree();

private:

};

#endif