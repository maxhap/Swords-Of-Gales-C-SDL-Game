#include "stdafx.h"

ItemHandler::ItemHandler()
{

}

ItemHandler::~ItemHandler()
{

}

void ItemHandler::AddRandomItem( int group, int x, int y )
{
	int itemNumber = rand() % 10;

	if( itemNumber == 1 )
	{
		Heart* heart = new Heart( Initialize::Heart, x, y,50, 41, Initialize::GameHeartImageLocation );
		heart->LoadItemImage();
	
		GameObjectHolder::instance().AddToItemContainer( heart );
	}
	else if( itemNumber == 2 )
	{
		RedPotion* potion = new RedPotion( Initialize::Potion, x, y, 50, 48, Initialize::GameRedPotionImageLocation, Initialize::InventoryItemRedPotionImageLocation, Initialize::InventoryItemRedPotionImageLocation );
	    potion->LoadItemImage();

		GameObjectHolder::instance().AddToItemContainer( potion );
	}
	else if( itemNumber >= 3 ||  itemNumber >= 7)
	{
		GreenRupee* rupee = new GreenRupee( Initialize::Rupee, x, y , 25, 55, Initialize::GameGreenRupeeImageLocation );
		rupee->LoadItemImage();

		GameObjectHolder::instance().AddToItemContainer( rupee );
	}
}

