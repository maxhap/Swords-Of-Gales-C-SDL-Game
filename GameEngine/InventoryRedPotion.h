#ifndef _INVENTORYREDPORTION_
#define _INVENTORYREDPORTION_

#include "stdafx.h"

class InventoryRedPotion : public InventoryItem
{

public:

	InventoryRedPotion( string inventoryBackgroundImageLocation, string inventoryActiveImageLocation  );
	~InventoryRedPotion();

	void InventoryUse();

private:


};

#endif