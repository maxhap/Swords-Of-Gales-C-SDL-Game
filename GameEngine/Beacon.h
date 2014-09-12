#ifndef _BEACON_
#define _BEACON_

#include "stdafx.h"
#include "EntryPoint.h"

class Beacon : public EntryPoint, public GameObject
{

public:

	Beacon( int objectType, string entryPointID, int x, int y, int width, int height, int startingAngle, int movementSpeed, string spriteLocation, bool isHittable );
	~Beacon();

	bool HasColided( GameObject* otherItem );

private:



};
#endif
