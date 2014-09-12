#include "stdafx.h"

ShopSpot::ShopSpot( int objectID, int x, int y, int width, int height, int startingAngle, int movementSpeed, string spriteLocation, bool isHittable ) : InteractableGameObject( objectID, x, y, width, height, startingAngle, movementSpeed, spriteLocation, isHittable, x, y, width, height )
{

}

ShopSpot::~ShopSpot()
{

}

void ShopSpot::Interact()
{
	//launch Shop and change game state
	cout << "launch shop";
	LevelSystem::instance().SetShopToDisplay( true );
}

bool ShopSpot::HasColided( GameObject* otherItem )
{
	return false;
}