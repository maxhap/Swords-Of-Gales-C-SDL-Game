#ifndef _INVENTORYSYSTEM_
#define _INVENTORYSYSTEM_

#include "stdafx.h"

class InventorySystem : public InventoryHolder
{

public:

	InventorySystem( int x, int y, int width, int height, string backgroundImageLocation, string activeImageLocation, int maxInventorySpace, int inventoryItemWidth, int inventoryItemHeight );
	~InventorySystem();

	bool AddInventoryItem( InventoryItem* item );
	void UseInventoryItem( int itemNumber );
	void DrawInventoryItems( MainWnd* window );
	void HandleInput( SDL_Event event );
	void DisableAllTogles();
	void AddPlayer( Player* player );

private:

	int _MaxInventorySpace;
	int _InventoryItemWidth;
	int _InventoryItemHeight; 

	InventoryItem* _pCurrentTogledAttackItem;	
	Player* _pPlayer;

};


#endif

