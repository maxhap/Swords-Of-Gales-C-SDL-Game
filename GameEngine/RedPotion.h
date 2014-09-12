#ifndef _REDPOTION_
#define _REDPOTION_

#include "stdafx.h"
#include "InventoryItem.h"

class RedPotion : public Item
{

public:

	RedPotion( int objectID, int x, int y, int width, int height, string spriteLocation, string inventoryBackgroundImageLocation, string inventoryActiveImageLocation );
	~RedPotion();

	//overloads
	bool Aquire();
	void InventoryUse();

	InventoryItem* ConvertToInventoryItem();

private:

	string _InventoryBackgroundImageLocation;
	string _InventoryActiveImageLocation;


};

#endif