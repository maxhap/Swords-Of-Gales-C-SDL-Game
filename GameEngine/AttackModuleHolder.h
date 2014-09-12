#ifndef _ATTACKMODUELHOLDER_
#define _ATTACKMODUELHOLDER_

#include "stdafx.h"

class Attack;

class AttackModuleHolder
{

public :

	AttackModuleHolder();
	~AttackModuleHolder();
	
	void AddAttack( Attack* attack );
	Attack* GetAttack( int attackIdentity );
	Attack* GetActiveAttack();

	vector<Attack*>* GetAttackList();

private:

	vector<Attack*>* _pAttackList;

};

#endif