#ifndef _HEARTSHOPITEM_
#define _HEARTSHOPITEM_

#include "stdafx.h"

class HeartShopItem : public ShopItem
{

public:
	 
	HeartShopItem( int id, int x, int y, int width, int height, string backgroundImage, int price, int restoreAmount );
	~HeartShopItem();

	void Buy();

private:

	int _RestoreAmount;

};

#endif