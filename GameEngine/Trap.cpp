#include "stdafx.h"

Trap::Trap( int objectID, int damage, int x, int y, int width, int height, string spriteLocation, int startingAngle, int movementSpeed, bool hittable ) : GameObject( objectID, x, y, width, height, startingAngle, movementSpeed, spriteLocation, hittable )
{
	_Damage = damage;
	_State = 0;
	_Active = false;
}

Trap::~Trap()
{

}

bool Trap::Update( bool nocollision, bool includeAI )
{
	return true;
}

bool Trap::GetIsActive()
{
	return _Active;
}

void Trap::SetIsActive( bool active )
{
	_Active = active;
}

void Trap::Animate()
{
}