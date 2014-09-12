#ifndef _PLAYER_
#define PLAYER_

#include "stdafx.h"
#include "AttackModuleHolder.h"
#include "InventoryItemHolder.h"

class Player : public Character, public AttackModuleHolder, public InventoryItemHolder, public Health
{

public:

	Player( int objectType, int x, int y, int width, int height, int startinAngle, int movementSpeed, string spriteLocation, int maxHealth, int healthAmount, bool isHittable, int RupeeAmount, int arrowAmount, int interactionX, int interactionY, int interactionWidth, int interactionHeight );
	~Player();

	bool ChangeRupeeAmount( int amount );
	void ChangeArrowAmount( int amount );

	int GetRupeeAmount();
	int GetArrowAmount();

	void TakeHit( int Damage );

private:

	int _RupeeAmount;
	int _ArrowAmount;

	//overrides
	void BuildSpriteMap();


};

#endif

