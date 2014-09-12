#ifndef _INVENTORYHOLDER_
#define _INVENTORYHOLDER_

#include "stdafx.h"

class InventoryHolder
{
public:

	InventoryHolder( int x, int y, int width, int height, string backgroundImageLocation, string activeImageLocation );
	~InventoryHolder();
	bool LoadInventoryImage();
	virtual void DrawInventory( MainWnd* window );

protected:
	
	SDL_Rect* _pInventoryContainer;
	GraphicsTexture* _pInventorySurface;
	GraphicsTexture* _pInventorySurfaceActive;

	string _InventoryBackgroundImageLocation;
	string _InventoryActiveImageLocation;


};

#endif
