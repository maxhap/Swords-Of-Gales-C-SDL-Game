#include "stdafx.h"

InventoryItem::InventoryItem( bool isTogle, string inventoryBackgroundImageLocation, string inventoryActiveImageLocation ) : InventoryHolder( 0, 0, 0, 0, inventoryBackgroundImageLocation, inventoryActiveImageLocation )
{
	_IsTogle = isTogle;
	_Active = false;
}

InventoryItem::~InventoryItem()
{

}

bool InventoryItem::GetIsTogle() const
{
	return _IsTogle;
}

void InventoryItem::InventoryUse() 
{

}

void InventoryItem::SetActive( bool active )
{
	_Active = active;
}

bool InventoryItem::GetActive()
{
	return _Active;
}

void InventoryItem::DrawInInventory( MainWnd* window, SDL_Rect position )
{
	if( _pInventorySurface != NULL && _InventoryBackgroundImageLocation != "" )
	{		
		SDL_Rect scale;
		scale.w = _pInventoryContainer->w;
		scale.h = _pInventoryContainer->h;
		scale.x = position.x;
		scale.y = position.y;
		
		if( _Active == true )
		{
			//blit active image
			window->RenderToScreen( _pInventorySurfaceActive, &scale, NULL );
		}
		else
		{
			//blit inactive image
			window->RenderToScreen( _pInventorySurfaceActive, &scale, NULL );
		}

	}
}
