#include "stdafx.h"

Character::Character( int objectType, int x, int y, int width, int height, int startinAngle, int movementSpeed, string spriteLocation, bool isHittable, int interactionX, int interactionY, int interactionWidth, int interactionHeight ) : InteractableGameObject( objectType, x, y, width, height, startinAngle, movementSpeed, spriteLocation, isHittable, interactionX, interactionY, interactionWidth, interactionHeight )
{
	_IsAnimating = false;	
}

Character::~Character()
{
}