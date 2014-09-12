#include "stdafx.h"
 
RedPotion::RedPotion( int objectID, int x, int y, int width, int height, string spriteLocation, string inventoryBackgroundImageLocation, string inventoryActiveImageLocation ) : Item( objectID, x, y , width, height, spriteLocation )
{
	_InventoryBackgroundImageLocation = inventoryBackgroundImageLocation;
	_InventoryActiveImageLocation = inventoryActiveImageLocation;
}

RedPotion::~RedPotion()
{

}

bool RedPotion::Aquire()
{
	return true;
}

InventoryItem* RedPotion::ConvertToInventoryItem()
{
	InventoryRedPotion* potion = new InventoryRedPotion( _InventoryBackgroundImageLocation, _InventoryActiveImageLocation );
	potion->LoadInventoryImage();

	return potion;
}