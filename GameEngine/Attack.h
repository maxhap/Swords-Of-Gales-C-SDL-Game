#ifndef _ATTACK_
#define _ATTACK_

#include "stdafx.h"

class Attack : public InventoryItem
{

public:

	Attack( int identity, int width, int height, int damage, int reach, GameObject* pObjectAttachedTo, bool isTogle, string backgroundImageLocation, string activeImageLocation );
	~Attack();
	
	virtual bool CheckHit( GameObject* otherObject );
	virtual void DrawTestRect( MainWnd* window, Camora* camora );

	void InventoryUse();
	virtual void UseAttack( CombatSystem* combatSystem );

	SDL_Rect* GetVirtualRect() const;

	int GetIdentity(); 
	int GetDamage();

	GameObject* GetObjectAttachedTo();

protected:

	SDL_Rect* _pVirtualContainer;

	int _Identity;
	int _Damage;
	int _Reach;
	GameObject* _pObjectAttachedTo;

	virtual bool  HasColided( GameObject* otherObject );
	
};

#endif