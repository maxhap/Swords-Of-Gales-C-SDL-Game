#ifndef _GAMEOBJECTFACTORY_
#define _GAMEOBJECTFACTORY_

#include "stdafx.h"

class GameObjectFactory : public Singleton<GameObjectFactory>
{

public:
	
	Player* GetPlayer();

	Hagle* GetHagle( int x, int y, int width, int height, int startinAngle, int movementSpeed, string spriteLocation, int healthAmount, bool isHittable, int damage, int areaOfSight );	

	Arrow* GetArrow( int damage, int angle, GameObject* objectThatFiredArrow );

	HealthHeart* GetHealthHeart( int HeartSize );

	Door* GetDoor( int x, int y, int width, int height, int startingAngle, string spriteLocation, string forwardLevel, string entryPointID );

	Beacon* GetBeacon( string entryPointID, int x, int y, int width, int height, int startingAngle, string spriteLocation );

	BigTree* GetBigTree( int x, int y, int width, int height, string spriteLocation );

	SpikeTrap* GetSpikeTrap( int x, int y, int width, int height, string spriteLocation, int activePeriod, int damage );

	Grass* GetGrass( int x, int y, int width, int height, string spriteLocation );

	House* GetHouse( int x, int y, int width, int height, string spriteLocation, int doorX, int doorY, int doorWidth, int doorHeight , string forwardLevel, string entryPointID );

	ShopSpot* GetShopSpot( int x, int y, int width, int height, string spriteLocation );
	
	Shop* GetShop( int x, int y, int width, int height, string spriteLocation );

	ArrowShopItem* GetArrowShopItem( int x, int y, int width, int height, string backgroundImage, int price, int restoreAmount );

	HeartShopItem* GetHeartShopItem( int x, int y, int width, int height, string backgroundImage, int price, int restoreAmount );

	int GetIdentity( int ObjectType );

private:
	
	friend class Singleton<GameObjectFactory>;
	GameObjectFactory();

	int _ObjectIdentityCounter;
	

};

#endif
