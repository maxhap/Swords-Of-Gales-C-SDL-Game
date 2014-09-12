#ifndef _SHOP_
#define _SHOP_

#include "stdafx.h"

class ShopItem;

class Shop : public Object
{

public:

	Shop( int objectID, int x, int y, int width, int height, string backgroundImageLocation );
	~Shop();

	void AddItem( ShopItem* item );
	void Draw( MainWnd* window, Camora* camora );
	void HandleInput( SDL_Event passedEvent );

private:	

	bool _Empty;

	vector<ShopItem*>* _pItemList;

	string _BackgroundImageLocation;
};

#endif