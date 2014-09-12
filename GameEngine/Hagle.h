#ifndef _HANGLE_
#define _HANGLE_

#include "stdafx.h"
#include "AttackModuleHolder.h" 

class Hagle : public MeeleEnemy
{

public:

	Hagle( int objectType, int x, int y, int width, int height, int startinAngle, int movementSpeed, string spriteLocation, int healthAmount, bool isHittable, int areaOfSight );
	~Hagle();

private:

	//overrides
	void BuildSpriteMap();

};



#endif