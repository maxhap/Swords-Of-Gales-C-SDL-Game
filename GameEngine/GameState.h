#ifndef _GAMESTATE_
#define _GAMESTATE_

#include "stdafx.h"

class GameState : public Singleton<GameState>
{

public:

	int static const WELCOMEDISPLAY = 0;
	int static const WELCOMETOLEVEL = 1;
	int static const LEVELTOLOADING = 2;
	int static const LEVELLOADING = 3;
	int static const LEVELLOADWAIT = 4;
	int static const GAMEPLAYEXPLOREMODE = 5;
	int static const GAMEPLAYSHOPMODE = 6;
	int static const GAMEPLAYTALKMODE = 7;
	int static const LEVELSWITCH = 8;
	int static const GAMEOVERDISPLAY = 9;

	~GameState();

	void SetGameState( int gameState );
	int GetGameState();

private:

	friend Singleton<GameState>;
	GameState();

	int _CurrentGameState;
};

#endif