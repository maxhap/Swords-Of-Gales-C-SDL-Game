#ifndef _INVENTORYITEM_
#define _INVENTORYITEM_

#include "stdafx.h"
#include "InventoryHolder.h"

class InventoryItem : public InventoryHolder
{
public:
	
	InventoryItem( bool isTogle, string inventoryBackgroundImageLocation, string inventoryActiveImageLocation );
	~InventoryItem();
	
	void virtual InventoryUse();
	void SetActive( bool active );
	bool GetActive();

	bool GetIsTogle() const;
	void DrawInInventory( MainWnd* window, SDL_Rect position );

protected :

	bool _IsTogle;
	bool _Active;
};	


#endif