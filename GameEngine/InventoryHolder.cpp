#include "stdafx.h"

InventoryHolder::InventoryHolder( int x, int y, int width, int height, string backgroundImageLocation, string activeImageLocation )
{
	_pInventoryContainer = new SDL_Rect();
	_pInventoryContainer->x = x;
	_pInventoryContainer->y = y;
	_pInventoryContainer->w = width;
	_pInventoryContainer->h = height;

	_InventoryBackgroundImageLocation = backgroundImageLocation; 
	_InventoryActiveImageLocation = activeImageLocation;
	_pInventorySurface = NULL;
	_pInventorySurfaceActive = NULL;

}

InventoryHolder::~InventoryHolder()
{
	delete _pInventoryContainer;
	delete _pInventorySurface;
	delete _pInventorySurfaceActive;
}


bool InventoryHolder::LoadInventoryImage()
{
	_pInventorySurface = ImageLoader::instance().Load( _InventoryBackgroundImageLocation );

	if( _pInventorySurface == NULL )
	{
		return false;
	}

	_pInventorySurfaceActive = ImageLoader::instance().Load( _InventoryActiveImageLocation );

	if( _pInventorySurfaceActive == NULL )
	{
		return false;
	}

	return true;
}

void InventoryHolder::DrawInventory( MainWnd* window )
{
	if( _pInventorySurface != NULL && _InventoryBackgroundImageLocation != "" )
	{
		//image in viewing space, blot without problem		 
		window->RenderToScreen( _pInventorySurface, _pInventoryContainer, NULL );
	}
}

