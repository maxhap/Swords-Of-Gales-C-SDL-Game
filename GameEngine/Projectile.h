#ifndef _PROJECTILE_
#define _PROJECTILE_

#include "stdafx.h"

class Projectile : public GameObject
{

public:

	Projectile( int objectType, int x, int y, int width, int height, int startingAngle, int movementSpeed, string spriteLocation, bool isHittable, int damage, int maxTravelDistance, GameObject* objectAttachedTo );
	~Projectile();

	int GetDamage() const;
	int GetMaxTravelDistance() const;
	int GetCurrentTravelDistance() const;

	virtual void Move();

	virtual bool TimeToDestroy();

	GameObject* GetObjectAttachedTo();

protected:

	int _Damage;
	int _MaxTravelDistance;
	int _CurrentTravelDistance;

	GameObject* _ObjectAttachedTo;

};

#endif