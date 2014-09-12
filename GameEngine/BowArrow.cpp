#include "stdafx.h"

BowArrow::BowArrow( int identity, int width, int height, int damage, int reach, GameObject* pObjectAttachedTo, bool isTogle, string backgroundImageLocation, string activeImageLocation  ) : Attack( identity, width, height, damage, reach, pObjectAttachedTo, isTogle, backgroundImageLocation, activeImageLocation )
{

}

BowArrow::~BowArrow()
{

}

void BowArrow::UseAttack( CombatSystem* combatSystem )
{
	bool create = true;
	
	if( _pObjectAttachedTo->GetObjectType() == Initialize::Player )
	{
		Player* player = ( Player* ) _pObjectAttachedTo;

		if( player->GetArrowAmount() > 0 )
		{
			player->ChangeArrowAmount( -1 );
		}
		else
		{
			create = false;
		}
	}

	if( create )
	{
		_pObjectAttachedTo->BowArrowAnimation();

		EventManager::instance().Add( combatSystem, this, &CombatSystem::CreateArrow );
	}
}