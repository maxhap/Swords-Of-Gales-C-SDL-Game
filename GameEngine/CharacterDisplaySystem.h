#ifndef _CHARACTERDISPLAYSYSTEM_
#define _CHARACTERDISPLAYSYSTEM_

#include "stdafx.h"

class Character;

class CharacterDisplaySystem : public DisplayHolder
{
public:

	CharacterDisplaySystem( int x, int y, int width, int height, string backgroundImageLocation );
	~CharacterDisplaySystem();

	void AddPlayer( Player* player );
	void DrawCharacterHealth( MainWnd* window );

private:

	Player* _pPlayer;


};


#endif
