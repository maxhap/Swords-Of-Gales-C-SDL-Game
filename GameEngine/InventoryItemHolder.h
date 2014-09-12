#ifndef _INVENTORYITEMHOLDER_
#define _INVENTORYITEMHOLDER_

#include "stdafx.h"

//class forwarder
class InventoryItem;

class InventoryItemHolder 
{

public:

	InventoryItemHolder();
	~InventoryItemHolder();

	void AddItem( InventoryItem* item );
	void RemoveItem( InventoryItem* item );
	void DeleteInventoryItems();


	vector<InventoryItem*>* GetInventoryList();

private:

	vector<InventoryItem*>* _pItemList;

};


#endif