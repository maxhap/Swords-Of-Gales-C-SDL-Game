#include "stdafx.h"

Health::Health( int maxHealth, int healthAmount )
{
	_CurrentHealth = healthAmount; 
	_MaxHealth = maxHealth;
}

Health::~Health()
{

}

int Health::GetCurrentHealth()
{
	return _CurrentHealth;
}

int Health::GetMaxHealth()
{
	return _MaxHealth;
}

void Health::ReduceHealth( int damage )
{
	_CurrentHealth -= damage;

	if( _CurrentHealth < 0 ) 
	{
		_CurrentHealth = 0;
	}
}

void Health::RestoreHealth( int recovery )
{
	_CurrentHealth += recovery;

	if( _CurrentHealth > _MaxHealth )
	{
		_CurrentHealth  = _MaxHealth;
	}
}
