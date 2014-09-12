#ifndef _GAMEEVENT_
#define _GAMEEVENT_

#include "stdafx.h"

class Attack;
class CombatSystem;
class GameObject;

typedef void ( CombatSystem::*Func )( void );
typedef void ( CombatSystem::*FuncA )( Attack* );

class GameEvent
{

public:

	GameEvent();
	~GameEvent();

	CombatSystem* _pCombatSystem;
	Attack* _pAttack;
	FuncA _pFunc;

};

#endif