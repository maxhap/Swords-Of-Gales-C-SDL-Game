#ifndef _ARROW_
#define _ARROW_

#include "stdafx.h"

class Arrow : public Projectile
{

public:

	Arrow( int objectType, int x, int y, int width, int height, int startingAngle, int movementSpeed, string spriteLocation, bool isHittable, int damage, int maxTravelDistance, GameObject* objectAttachedTo );
	~Arrow();	

	bool Update( bool nocollision, bool includeAI = false );

	bool TimeToDestroy();

private:

};

#endif