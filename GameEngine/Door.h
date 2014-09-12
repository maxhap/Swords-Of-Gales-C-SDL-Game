#ifndef _DOOR_
#define _DOOR_

#include "stdafx.h"
#include "ExitPoint.h"

class Door : public GameObject, public ExitPoint
{

public:

	Door( int objectType, int x, int y, int width, int height, int startingAngle, string spriteLocation, string forwardLevel, string entryPointID );
	~Door();

	inline bool HasColided( GameObject* otherItem );

private:

};

#endif