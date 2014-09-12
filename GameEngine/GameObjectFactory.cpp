#include "stdafx.h"

GameObjectFactory::GameObjectFactory()
{
	_ObjectIdentityCounter = 0;
}

int GameObjectFactory::GetIdentity( int ObjectType )
{
	_ObjectIdentityCounter++;

	int id = ObjectType * 1000 + _ObjectIdentityCounter;

	return _ObjectIdentityCounter; 
}

Player* GameObjectFactory::GetPlayer()
{
	Player* player = new Player( GetIdentity( Initialize::Player ), 10, 10, Initialize::CharacterWidth, Initialize::CharacterHeight, 90, Initialize::MovementSpeed, Initialize::CharacterSpriteLocation, Initialize::CharacterMaxHealth, Initialize::CharacterMaxHealth, true, 100, Initialize::CharacterStartingArrows, 0, 0, 0, 0 );

	//sword attack
	SwordAttack* sword = new SwordAttack( GetIdentity( Initialize::SwordAttack ), 50, 50, 100, 50, player, true, Initialize::InventoryItemSwordImageLocation, Initialize::InventoryItemSwordActiveImageLocation );
	sword->SetActive( true );

	if ( sword->LoadInventoryImage() == false )
	{
		return NULL;
	}

	player->AddAttack( sword ); 

	//bow arrow
	BowArrow* bowArrow = new BowArrow( GetIdentity( Initialize::BowArrowAttack ), 50, 50, 100, 50, player, true, Initialize::InventoryItemBowArrowImageLocation, Initialize::InventoryItemBowArrowActiveImageLocation );

	if ( bowArrow->LoadInventoryImage() == false )
	{
		return NULL;
	}

	player->AddAttack( bowArrow ); 

	return player;
}

HealthHeart* GameObjectFactory::GetHealthHeart( int HeartSize )
{
	HealthHeart* heart = NULL;

	if( HeartSize == Initialize::Heart100ID )
	{
		heart = new HealthHeart( 0, 0, Initialize::HeartWidth, Initialize::HeartHeight, Initialize::FullHeartBackgroundLocation );
	}
	else if( HeartSize == Initialize::Heart34ID )
	{
		heart = new HealthHeart( 0, 0, Initialize::HeartWidth, Initialize::HeartHeight, Initialize::ThreeHeartBackgroundLocation );
	}
	else if( HeartSize == Initialize::Heart12ID )
	{
		heart = new HealthHeart( 0, 0, Initialize::HeartWidth, Initialize::HeartHeight, Initialize::HalfHeartBackgroundLocation );
	}
	else if( HeartSize == Initialize::Heart14ID )
	{
		heart = new HealthHeart( 0, 0, Initialize::HeartWidth, Initialize::HeartHeight, Initialize::OneHeartBackgroundLocation );
	}

	if( heart != NULL )
	{
		heart->LoadDisplayImage();
	}
	
	return heart;
}

Arrow* GameObjectFactory::GetArrow( int damage, int angle, GameObject* objectThatFiredArrow )
{
	Arrow* arrow = new Arrow( GetIdentity( Initialize::Arrow ), 0, 0, Initialize::ArrowWidth, Initialize::ArrowHeight, angle, Initialize::ArrowSpeed, Initialize::ArrowSpriteLocation, false, damage, Initialize::ArrowMaxTravelDistance, objectThatFiredArrow );
	arrow->LoadItemImage();

	return arrow;
}

Hagle* GameObjectFactory::GetHagle( int x, int y, int width, int height, int startinAngle, int movementSpeed, string spriteLocation, int healthAmount, bool isHittable, int damage, int areaOfSight )
{
	Hagle* hagle = new Hagle( GetIdentity( Initialize::Hagle ), x, y, width, height, startinAngle, movementSpeed, spriteLocation, healthAmount, isHittable, areaOfSight );

	//sword attack
	SwordAttack* sword = new SwordAttack( GetIdentity( Initialize::SwordAttack ), 50, 50, damage, 50, hagle, true, Initialize::InventoryItemSwordImageLocation, Initialize::InventoryItemSwordActiveImageLocation );
	sword->SetActive( true );

	if ( sword->LoadInventoryImage() == false )
	{
		return NULL;
	}

	hagle->AddAttack( sword );

	return hagle;
}

Door* GameObjectFactory::GetDoor( int x, int y, int width, int height, int startingAngle, string spriteLocation, string forwardLevel, string entryPointID )
{
	Door* door = new Door( GetIdentity( Initialize::Door ), x, y, width, height, startingAngle, spriteLocation, forwardLevel, entryPointID );

	return door;
}

Beacon* GameObjectFactory::GetBeacon( string entryPointID, int x, int y, int width, int height, int startingAngle, string spriteLocation )
{
	Beacon* beacon = new Beacon( GetIdentity( Initialize::Beacon ), entryPointID, x, y, width, height, startingAngle, 0, spriteLocation, false );
	beacon->SetAlwaysDrawBefore( true );

	return beacon;
}

BigTree* GameObjectFactory::GetBigTree( int x, int y, int width, int height, string spriteLocation )
{
	BigTree* bigTree = new BigTree( GetIdentity( Initialize::BigTree ), x, y, width, height, 0, 0, spriteLocation, true );

	return bigTree;
}

SpikeTrap* GameObjectFactory::GetSpikeTrap( int x, int y, int width, int height, string spriteLocation, int activePeriod, int damage )
{
	SpikeTrap* spikeTrap = new SpikeTrap( GetIdentity( Initialize::SpikeTrap ), damage, activePeriod, x, y, width, height, spriteLocation, 0, 0, false );
	spikeTrap ->SetAlwaysDrawBefore( true );

	return spikeTrap;
}

Grass* GameObjectFactory::GetGrass( int x, int y, int width, int height, string spriteLocation )
{
	Grass* grass = new Grass( GetIdentity( Initialize::Grass ), x, y, width, height, 0, 0, spriteLocation, false );

	return grass;
}

House* GameObjectFactory::GetHouse( int x, int y, int width, int height, string spriteLocation, int doorX, int doorY, int doorWidth, int doorHeight , string forwardLevel, string entryPointID )
{
	House* house = new House( GetIdentity( Initialize::House ), x, y, width, height, 0, 0, spriteLocation, false, doorX, doorY, doorWidth, doorHeight, forwardLevel, entryPointID );

	return house;
}

ShopSpot* GameObjectFactory::GetShopSpot( int x, int y, int width, int height, string spriteLocation )
{
	ShopSpot* shopSpot = new ShopSpot( GetIdentity( Initialize::ShopSpot ), x, y, width, height, 0, 0, spriteLocation, false );
	shopSpot->SetAlwaysDrawBefore( true );

	return shopSpot;
}

Shop* GameObjectFactory::GetShop( int x, int y, int width, int height, string spriteLocation )
{
	Shop* shop = new Shop( GetIdentity( Initialize::Shop ), x, y, width, height, spriteLocation );

	return shop;
}

ArrowShopItem* GameObjectFactory::GetArrowShopItem( int x, int y, int width, int height, string backgroundImage, int price, int restoreAmount )
{
	ArrowShopItem* arrow = new ArrowShopItem( GetIdentity( Initialize::ArrowShopItem ), x, y, width, height, backgroundImage, price, restoreAmount );

	return arrow;
}

HeartShopItem* GameObjectFactory::GetHeartShopItem( int x, int y, int width, int height, string backgroundImage, int price, int restoreAmount )
{
	HeartShopItem* heart = new HeartShopItem( GetIdentity( Initialize::ArrowShopItem ), x, y, width, height, backgroundImage, price, restoreAmount );

	return heart;
}