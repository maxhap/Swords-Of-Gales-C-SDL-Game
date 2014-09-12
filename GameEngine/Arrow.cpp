#include "stdafx.h"

Arrow::Arrow( int objectType, int x, int y, int width, int height, int startingAngle, int movementSpeed, string spriteLocation, bool isHittable, int damage, int maxTravelDistance, GameObject* objectAttachedTo ) : Projectile( objectType, x, y, width, height, startingAngle, movementSpeed, spriteLocation, isHittable, damage, maxTravelDistance, objectAttachedTo )
{
}

Arrow::~Arrow()
{

}

bool Arrow::Update( bool nocollision, bool includeAI )
{
	if( !_IsCreatable )
	{
		return false;
	}

	ProcessAnimation( nocollision );

	int xIncrease = int ( cos( ( GetDirection() + 0.0 ) * M_PI / 180.0 ) * _MovementSpeed );
	int yIncrease= int ( sin( ( GetDirection() + 0.0 ) * M_PI / 180.0 ) * _MovementSpeed );

	_Container->x += xIncrease;
	_Container->y += yIncrease;

	_CurrentTravelDistance += _MovementSpeed;

	return true;

}

bool Arrow::TimeToDestroy()
{
	if( _CurrentTravelDistance >= _MaxTravelDistance )
	{
		return true;
	}

	return false;
}