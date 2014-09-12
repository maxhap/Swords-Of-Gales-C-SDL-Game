#include "stdafx.h"

AttackModuleHolder::AttackModuleHolder()
{
	_pAttackList = new vector<Attack*>;
}

AttackModuleHolder::~AttackModuleHolder()
{

	for( vector<Attack*>::iterator i = _pAttackList->begin(); i < _pAttackList->end(); i++ )
	{
		delete ( *i );
	}

	_pAttackList->erase( _pAttackList->begin(), _pAttackList->end() ); 

	delete _pAttackList;
}

vector<Attack*>* AttackModuleHolder::GetAttackList()
{
	return _pAttackList;	
}
	
void AttackModuleHolder::AddAttack( Attack* attack )
{
	_pAttackList->insert( _pAttackList->end(), 1, attack );
}

Attack* AttackModuleHolder::GetAttack( int attackIdentity )
{
	for( vector<Attack*>::iterator i = _pAttackList->begin(); i < _pAttackList->end(); i ++ )
	{
		if ( ( *i )->GetIdentity() == attackIdentity )
		{
			return ( *i );
		}
	}

	return NULL;
}

Attack* AttackModuleHolder::GetActiveAttack()
{
	for( vector<Attack*>::iterator i = _pAttackList->begin(); i < _pAttackList->end(); i ++ )
	{
		if ( ( *i )->GetActive() == true )
		{
			return ( *i );
		}
	}

	return NULL;
}


