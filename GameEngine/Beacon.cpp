#include "stdafx.h"

Beacon::Beacon( int objectType, string entryPointID, int x, int y, int width, int height, int startingAngle, int movementSpeed, string spriteLocation, bool isHittable ): EntryPoint( entryPointID, x, y ), GameObject( objectType, x, y, width, height, startingAngle, movementSpeed, spriteLocation, isHittable )
{
	_ObjectType = Initialize::Beacon;
}

Beacon::~Beacon()
{

}

bool Beacon::HasColided( GameObject* otherItem )
{
	return false;
}