#ifndef _LEVELSYSTEM_
#define _LEVELSYSTEM_

#include "stdafx.h"

class LevelSystem : public Singleton<LevelSystem> 
{

public:

	~LevelSystem();

	Level* GetCurrentLevel();

	bool LoadWelcomeScreen( string welcomeFileScreenLocation );
	bool LoadLevel( string levelFile );

	bool DestroyCurrentLevel();
	bool GetLevelToSwitch();
	bool GetShopToDisplay();

	string GetNextLevelFileLocation();
	string GetNextLevelEntryPointID();

	void SetNextLevelFileLocation( string location );
	void SetNextLevelEntryPointID( string id );
	void SetLevelToSwitch( bool toSwitch );
	void SetShopToDisplay( bool toDisplay );

private:

	string _NextLevelFileLocation;
	string _NextLevelEntryPointID;

	bool _LevelToSwitch;
	bool _ShopToDisplay;

	friend Singleton<LevelSystem>;
	LevelSystem();

	Level* _CurrentLevel;

	bool LoadLevelProperties( string levelFile );
	bool LoadLevelItems( string levelFile );
};

#endif