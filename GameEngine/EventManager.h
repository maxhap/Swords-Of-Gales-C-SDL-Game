#ifndef _EventManager_
#define _EventManager_

#include "stdafx.h"

class GameEvent;
class CombatSystem;
class Attack;

typedef void ( CombatSystem::*Func )( void );
typedef void ( CombatSystem::*FuncA )( Attack* );

class EventManager : public Singleton<EventManager>
{

public:

	void Add(CombatSystem* pSystem, Attack* attackObject, FuncA pFuncA );
	void Remove( GameEvent* pGameEvent );
	void AddToRemoveQueue( GameEvent* pGameEvent );
	void OnIdle();

private:

	friend class Singleton<EventManager>;

	EventManager();
	~EventManager();

	vector<GameEvent*>* _pEventList;
	vector<GameEvent*>* _pRemoveList;

};

#endif