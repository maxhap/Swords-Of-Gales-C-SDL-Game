#include "stdafx.h"

InventoryRedPotion::InventoryRedPotion( string inventoryBackgroundImageLocation, string inventoryActiveImageLocation  ) : InventoryItem( false, inventoryBackgroundImageLocation, inventoryActiveImageLocation )
{

}

InventoryRedPotion::~InventoryRedPotion()
{

}

void  InventoryRedPotion::InventoryUse()
{
	GameObjectHolder::instance().GetPlayer()->RestoreHealth( 12 );
}