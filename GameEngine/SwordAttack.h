#ifndef _COMBATSYSTEMSWORDATTACK_
#define _COMBATSYSTEMSWORDATTACK_

#include "stdafx.h"

class SwordAttack : public Attack
{

public:

	SwordAttack( int identity, int width, int height, int damage, int reach, GameObject* objectAttachedTo, bool isTogle, string backgroundImageLocation, string activeImageLocation );
	~SwordAttack();

	bool CheckHit( GameObject* otherObject );

	void UseAttack ( CombatSystem* combatSystem );
	void DrawTestRect( MainWnd* window, Camora* camora );

private:

	bool HasColided( GameObject* otherObject );
};

#endif