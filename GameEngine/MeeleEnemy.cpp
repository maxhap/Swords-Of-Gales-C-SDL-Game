#include "stdafx.h"

MeeleEnemy::MeeleEnemy( int objectType, int x, int y, int width, int height, int startinAngle, int movementSpeed, string spriteLocation, int healthAmount, bool isHittable, int areaOfSight ) : GameObject( objectType, x, y, width, height, startinAngle, movementSpeed, spriteLocation, isHittable ), AttackModuleHolder(), InventoryItemHolder(), Health( healthAmount, healthAmount ), ArtificialIntelligence( areaOfSight )
{
	//pass self to AI
	_GameObject = this;
}

MeeleEnemy::~MeeleEnemy()
{
}

void MeeleEnemy::TakeHit( int Damage )
{
	ReduceHealth( Damage );

	if( _CurrentHealth <= 0 )
	{
		_IsCreatable = false;
	}
}

bool MeeleEnemy::Update( bool noCollision, bool includeAI )
{
	if( includeAI == false )
	{
		return GameObject::Update( noCollision );
	}
	else
	{
		ProccessAI();
	}

	return true;
}

void MeeleEnemy::ProccessAI()
{
	Character* player = GameObjectHolder::instance().GetPlayer();

	int difx = abs( player->Container()->x - Container()->x );
	int dify = abs( player->Container()->y - Container()->y );

	int distnace = ( int ) sqrt( difx + dify + 0.0 );
	distnace = abs( distnace );

	if( distnace > 10 )
	{
		ArtificialIntelligence::ProccessAI();
	}
	else
	{
		int todo = rand() % 50 + 1;

		if( todo == 1 )
		{
			Attack* activeAttack = GetActiveAttack();

			CombatSystem::instance().ProcessAttackOnPlayer( activeAttack );
		}
		else
		{
			ArtificialIntelligence::ProccessAI();
		}
	}
}