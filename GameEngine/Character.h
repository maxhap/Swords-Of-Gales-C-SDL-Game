#ifndef _CHARACTER_
#define _CHARACTER_

#include "stdafx.h"

class Character : public InteractableGameObject
{

public:

	Character( int objectType, int x, int y, int width, int height, int startinAngle, int movementSpeed, string spriteLocation, bool isHittable, int interactionX, int interactionY, int interactionWidth, int interactionHeight );
	~Character();

	inline bool Update( bool nocollision ) { return GameObject::Update( nocollision ); }

private:

};



#endif