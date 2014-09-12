#include "stdafx.h"


LevelSystem::LevelSystem()
{
	_CurrentLevel = NULL;
	_LevelToSwitch = false;
	_ShopToDisplay = false;
}

LevelSystem::~LevelSystem()
{
	delete _CurrentLevel;
}

Level* LevelSystem::GetCurrentLevel()
{
	return _CurrentLevel;
}

bool LevelSystem::LoadWelcomeScreen( string welcomeFileScreenLocation )
{
	_CurrentLevel = new Level( welcomeFileScreenLocation );

	return _CurrentLevel->LoadAsStartScreen();
}

bool LevelSystem::LoadLevel( string levelFile )
{
	if( LoadLevelProperties( levelFile ) == false )
	{
		return false;
	}

	TileObjectHolder::instance().BuildSectors();
	GameObjectHolder::instance().BuildSectors();

	if( LoadLevelItems( levelFile ) == false )
	{
		return false;
	}

	return true;

}

bool LevelSystem::LoadLevelProperties( string levelFile )
{
	_CurrentLevel = new Level( levelFile );

	return _CurrentLevel->LoadProperties();
}

bool LevelSystem::LoadLevelItems( string levelFile )
{
	if( _CurrentLevel->LoadShop() == false )
	{
		return false;
	}

	if( _CurrentLevel->LoadTiles() == false )
	{
		return false;
	}

	if( _CurrentLevel->LoadEnemies() == false )
	{
		return false;
	}

	if( _CurrentLevel->LoadObjects() == false )
	{
		return false;
	}

	return true;
}

bool LevelSystem::DestroyCurrentLevel()
{
	GameObjectHolder::instance().DestroySectors();
	GameObjectHolder::instance().EmptyContainer();
	GameObjectHolder::instance().EmptyItemContainer();

	TileObjectHolder::instance().DestroySectors();	

	delete _CurrentLevel;

	_CurrentLevel = NULL;

	return true;
}

string LevelSystem::GetNextLevelFileLocation()
{
	return _NextLevelFileLocation;
}

string LevelSystem::GetNextLevelEntryPointID()
{
	return _NextLevelEntryPointID;
}

void LevelSystem::SetNextLevelFileLocation( string location )
{
	_NextLevelFileLocation = location;
}

void LevelSystem::SetNextLevelEntryPointID( string id )
{
	_NextLevelEntryPointID = id;
}

bool LevelSystem::GetLevelToSwitch()
{
	return _LevelToSwitch;
}

void LevelSystem::SetLevelToSwitch( bool toSwitch )
{
	_LevelToSwitch = toSwitch;
}

bool LevelSystem::GetShopToDisplay()
{
	return _ShopToDisplay;
}

void LevelSystem::SetShopToDisplay( bool toDisplay )
{
	_ShopToDisplay = toDisplay;
}