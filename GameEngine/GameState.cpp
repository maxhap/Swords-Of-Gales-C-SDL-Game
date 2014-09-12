#include "stdafx.h"

GameState::GameState()
{
	//for debug use  GAMEPLAYEXPLOREMODE
	_CurrentGameState = WELCOMEDISPLAY;
}

GameState::~GameState()
{
}

void GameState::SetGameState( int gameState )
{
	_CurrentGameState = gameState;
}

int GameState::GetGameState()
{
	return _CurrentGameState;
}