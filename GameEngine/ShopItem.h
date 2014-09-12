#ifndef _SHOPITEM_
#define _SHOPITEM_

#include "stdafx.h"

class ShopItem : public Object
{
	
public:

	ShopItem( int id, int x, int y, int width, int height, string backgroundImage, int price );
	~ShopItem();

	bool GetIsSelected();

	virtual void Buy();

	void Draw( MainWnd* window, Camora* camora );
	void SetIsSelected( bool selected );
	
	int GetPrice();

protected:

	SDL_Rect* _pContainer;

	bool _IsSelected;

	int _Price;
};

#endif