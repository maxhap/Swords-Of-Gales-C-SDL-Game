#ifndef _ARROWSHOPITEM_
#define _ARROWSHOPITEM_

#include "stdafx.h"

class ArrowShopItem : public ShopItem
{

public:

	ArrowShopItem( int id, int x, int y, int width, int height, string backgroundImage, int price, int restoreAmount );
	~ArrowShopItem();

	void Buy();

private:

	int _RestoreAmount;
};


#endif