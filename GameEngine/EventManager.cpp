#include "stdafx.h"

EventManager::EventManager()
{
	_pEventList = new std::vector<GameEvent*>;
	_pRemoveList = new std::vector<GameEvent*>;
}

EventManager::~EventManager()
{
	MemoryManagement<GameEvent>::instance().CleanVector( _pEventList, true );
	MemoryManagement<GameEvent>::instance().CleanVector( _pRemoveList, true );
}

void EventManager::Add(CombatSystem* pSystem, Attack* attackObject, FuncA pFuncA )
{

	GameEvent* pEvt = new GameEvent();
	pEvt->_pCombatSystem = pSystem;
	pEvt->_pAttack = attackObject;
	pEvt->_pFunc = pFuncA;

	_pEventList->insert(_pEventList->end(), 1, pEvt);
}

void EventManager::Remove( GameEvent* pEnt )
{
	for( vector<GameEvent*>::iterator i = _pEventList->begin(); i < _pEventList->end(); i++ )
	{
		if( ( *i ) == pEnt )
		{
			delete ( *i );
			_pEventList->erase( i );
			break;			
		}
	}
}

void EventManager::OnIdle()
{
	for( std::vector<GameEvent*>::iterator i = _pEventList->begin(); i < _pEventList->end(); i++ )
	{
		GameEvent* pEvt = ( *i );

		if (pEvt->_pAttack->GetObjectAttachedTo()->GetIsAnimating() == false )
		{
			FuncA pFunc = pEvt->_pFunc;
			CombatSystem* pSystem = pEvt->_pCombatSystem;

			( ( *pSystem ).*pFunc )( pEvt->_pAttack );

			AddToRemoveQueue( pEvt );
		}
	}

	//clean up
	for( std::vector<GameEvent*>::iterator i = _pRemoveList->begin(); i < _pRemoveList->end(); i++ )
	{
		for( std::vector<GameEvent*>::iterator z = _pEventList->begin(); z < _pEventList->end(); z++ )
		{
			if( ( *i ) == ( *z ))
			{
				delete ( *z );
				_pEventList->erase( z );
				break;
			}
		}
	}

	MemoryManagement<GameEvent>::instance().EmptyVector(_pRemoveList, false);

}

void EventManager::AddToRemoveQueue( GameEvent* pGameEvent )
{
	_pRemoveList->insert( _pRemoveList->end(), 1, pGameEvent );
}