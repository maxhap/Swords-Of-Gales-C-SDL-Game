#include "stdafx.h"

Hittable::Hittable( bool isHittable )
{
	_IsHittable = isHittable;
}
Hittable::~Hittable()
{
}

bool Hittable::GetIsHittable()
{
	return _IsHittable;
}

void Hittable::TakeHit( int dmg )
{
	//virtual overloaded in sub class
}