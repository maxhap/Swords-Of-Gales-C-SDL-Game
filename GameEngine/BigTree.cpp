#include "stdafx.h"

BigTree::BigTree( int objectID, int x, int y, int width, int height, int startingAngle, int movementSpeed, string spriteLocation, bool isHittable ): GameObject( objectID, x, y, width, height, startingAngle, movementSpeed, spriteLocation, isHittable )
{
	_ObjectType = Initialize::BigTree;
	_EntityType = Initialize::Blocker;	
}

BigTree::~BigTree()
{
}
