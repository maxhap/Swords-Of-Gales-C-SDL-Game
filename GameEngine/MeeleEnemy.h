#ifndef _MEELEENEMY
#define _MEELEENEMY

#include "stdafx.h"
#include "AttackModuleHolder.h" 

class MeeleEnemy : public GameObject, public AttackModuleHolder, public InventoryItemHolder, public Health, public ArtificialIntelligence
{

public:

	MeeleEnemy( int objectType, int x, int y, int width, int height, int startinAngle, int movementSpeed, string spriteLocation, int healthAmount, bool isHittable, int areaOfSight );
	~MeeleEnemy();

	inline bool Update( bool nocollision, bool includeAI = false );

	//overrides
	void TakeHit( int Damage );
	inline void ProccessAI();

private:


};

#endif