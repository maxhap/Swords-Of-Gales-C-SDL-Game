#include "stdafx.h"

CharacterDisplaySystem::CharacterDisplaySystem( int x, int y, int width, int height, string backgroundImageLocation ) : DisplayHolder( x, y, width, height, backgroundImageLocation )
{

}

CharacterDisplaySystem::~CharacterDisplaySystem()
{

}


void CharacterDisplaySystem::AddPlayer( Player* player )
{
	_pPlayer = player;
}

void CharacterDisplaySystem::DrawCharacterHealth( MainWnd* window )
{
	int health = _pPlayer->GetCurrentHealth();

	int sx = GetContainer()->x + 20;
	int sy = GetContainer()->y + 15;

	int x = sx;
	int y = sy;

	while( health > 0 )
	{
		HealthHeart* heart = NULL;

		//which heart to draw
		if( health >= 4 )
		{
			heart = GameObjectFactory::instance().GetHealthHeart( Initialize::Heart100ID );
		}
		else if ( health == 3 )
		{
			heart = GameObjectFactory::instance().GetHealthHeart( Initialize::Heart34ID );
			health = 0;
		}
		else if ( health == 2 )
		{
			heart = GameObjectFactory::instance().GetHealthHeart( Initialize::Heart12ID );
			health = 0;
		}
		else if ( health == 1 )
		{
			heart = GameObjectFactory::instance().GetHealthHeart( Initialize::Heart14ID );
			health = 0;
		}

		if( heart != NULL )
		{
			heart->SetPosition( x, y );

			x += heart->GetContainer()->w;

			heart->DrawDisplay( window );

			//set for next heart
			if( ( x + heart->GetContainer()->w ) > ( GetContainer()->x + GetContainer()->w ) )
			{
				x = sx;
				y += heart->GetContainer()->h;
			}

			delete heart;

			//deduct for next heart
			health -= 4; 
		}
		else
		{
			if( Initialize::TestMode == true )
			{
				cout << "Heart Draw Error";
			}

			break;
		}
	}
}
