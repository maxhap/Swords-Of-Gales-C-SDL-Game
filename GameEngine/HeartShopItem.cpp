#include "stdafx.h"

HeartShopItem::HeartShopItem( int id, int x, int y, int width, int height, string backgroundImage, int price, int restoreAmount ) : ShopItem( id, x, y, width, height, backgroundImage, price )
{
	_RestoreAmount= restoreAmount;
}

HeartShopItem::~HeartShopItem()
{

}

void HeartShopItem::Buy()
{
	if( GameObjectHolder::instance().GetPlayer()->ChangeRupeeAmount( -_Price ) )
	{
		GameObjectHolder::instance().GetPlayer()->RestoreHealth( _RestoreAmount );
	}
}