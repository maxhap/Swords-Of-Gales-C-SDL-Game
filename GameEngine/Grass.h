#ifndef _GRASS_
#define _GRASS_

#include "stdafx.h"

class Grass : public GameObject
{

public:

	Grass( int objectID, int x, int y, int width, int height, int startingAngle, int movementSpeed, string spriteLocation, bool isHittable );
	~Grass();

	inline bool HasColided( GameObject* otherItem );

private:

	bool WithinToCropSprite( SDL_Rect* otherObject );

};

#endif