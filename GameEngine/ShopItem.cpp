#include "stdafx.h"

ShopItem::ShopItem( int id, int x, int y, int width, int height, string backgroundImage, int price ) : Object( id, x,y, width, height, backgroundImage )
{
	_pContainer = new SDL_Rect();
	_pContainer->x = x;
	_pContainer->y = y;
	_pContainer->h = height;
	_pContainer->w = width;
	
	_IsSelected = false;

	_Price = price;
}

ShopItem::~ShopItem()
{
	delete _pContainer;
}

bool ShopItem::GetIsSelected()
{
	return _IsSelected;
}

void ShopItem::Buy()
{
	ErrorSystem::instance().WriteError( "Shop Item buy not impelemented" );	
}

int ShopItem::GetPrice()
{
	return _Price;
}

void ShopItem::SetIsSelected( bool selected )
{
	_IsSelected = selected;
}


void ShopItem::Draw( MainWnd* window, Camora* camora )
{
	SDL_Rect clip;
		
	clip.w = _pContainer->w;
	clip.h = _pContainer->h;
	clip.y = 0;
	clip.y = 0;

	if( _IsSelected )
	{
		clip.x = _pContainer->w;		
	}
	else
	{		
		clip.x = 0;		
	}

	window->RenderToScreen( _pSprite, _pContainer, &clip );
}