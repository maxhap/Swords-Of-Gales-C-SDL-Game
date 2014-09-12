#ifndef _HOUSE_
#define _HOUSE_

#include "stdafx.h"

class House : public ExitPoint, public GameObject
{

public:

	House( int objectType, int x, int y, int width, int height, int startingAngle, int movementSpeed, string spriteLocation, bool isHittable, int doorX, int doorY, int doorWidth, int doorHeight , string forwardLevel, string entryPointID );
	~House();

	inline bool HasColided( GameObject* otherItem );

private:

	SDL_Rect* _pDoor;

};

#endif