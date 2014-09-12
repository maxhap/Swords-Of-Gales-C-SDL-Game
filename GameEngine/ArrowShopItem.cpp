#include "stdafx.h"

ArrowShopItem::ArrowShopItem( int objectID, int x, int y, int width, int height, string backgroundImage, int price, int restoreAmount ) : ShopItem( objectID, x, y, width, height, backgroundImage, price )
{
	_RestoreAmount = restoreAmount;
}

ArrowShopItem::~ArrowShopItem()
{

}

void ArrowShopItem::Buy()
{
	GameObjectHolder::instance().GetPlayer()->ChangeRupeeAmount( -_Price );
	GameObjectHolder::instance().GetPlayer()->ChangeArrowAmount( _RestoreAmount );
}
