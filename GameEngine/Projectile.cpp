#include "stdafx.h"

Projectile::Projectile( int objectType, int x, int y, int width, int height, int startingAngle, int movementSpeed, string spriteLocation, bool isHittable, int damage, int maxTravelDistance, GameObject* objectAttachedTo ) : GameObject( objectType, x, y, width, height, startingAngle, movementSpeed, spriteLocation, isHittable )
{
	_Damage = damage;
	_MaxTravelDistance = maxTravelDistance;
	_CurrentTravelDistance = 0;
	_ObjectAttachedTo = objectAttachedTo;
}

Projectile::~Projectile()
{

}

int Projectile::GetDamage() const
{
	return _Damage;
}

int Projectile::GetMaxTravelDistance() const
{
	return _MaxTravelDistance;
}

int Projectile::GetCurrentTravelDistance() const
{
	return _CurrentTravelDistance;
}

void Projectile::Move()
{
}

bool Projectile::TimeToDestroy()
{
	return false;
}

GameObject* Projectile::GetObjectAttachedTo()
{
	return _ObjectAttachedTo;
}