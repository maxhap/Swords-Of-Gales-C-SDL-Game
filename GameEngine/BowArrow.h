#ifndef _BOWARROW_
#define _BOWARROW_

#include "stdafx.h"

class BowArrow : public Attack
{

public:

	BowArrow( int identity, int width, int height, int damage, int reach, GameObject* pObjectAttachedTo, bool isTogle, string backgroundImageLocation, string activeImageLocation  );
	~BowArrow();

	void UseAttack( CombatSystem* combatSystem );

private:


};

#endif