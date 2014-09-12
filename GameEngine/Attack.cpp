#include "stdafx.h"


Attack::Attack( int identity, int width, int height, int damage, int reach, GameObject* pObjectAttachedTo, bool isTogle, string backgroundImageLocation, string activeImageLocation  ) : InventoryItem( isTogle, backgroundImageLocation, activeImageLocation )
{
	_Damage = damage;
	_Reach = reach;
	_pObjectAttachedTo = pObjectAttachedTo;

	_pVirtualContainer = new SDL_Rect();
	_pVirtualContainer->w = width;
	_pVirtualContainer->h = height;

	_Identity = identity;

}

Attack::~Attack()
{
	delete _pVirtualContainer;
}

SDL_Rect* Attack::GetVirtualRect() const
{
	return _pVirtualContainer;
}

	
bool Attack::CheckHit( GameObject* otherObject )
{
	return true;
}

bool Attack::HasColided( GameObject* otherObject )
{
	return true;
}

int Attack::GetIdentity()
{
	return _Identity;
}

int Attack::GetDamage()
{
	return _Damage;
}

void Attack::InventoryUse()
{
	if( _Active == false )
	{
		_Active = true;
	}
	else
	{
		_Active = false;
	}
}


GameObject* Attack::GetObjectAttachedTo()
{
	return _pObjectAttachedTo;
}

void Attack::UseAttack( CombatSystem* combatSystem )
{
}

void Attack::DrawTestRect( MainWnd* window, Camora* camora )
{
}


