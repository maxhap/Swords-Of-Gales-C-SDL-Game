#ifndef _ITEM_
#define _ITEM_

#include "stdafx.h"

class Item : public Object
{

public:

	Item( int objectID, int x, int y, int width, int height, string spriteLocation );
	~Item();

	void AttachCharacter( Character* character );

	virtual bool Aquire();

	virtual InventoryItem* ConvertToInventoryItem();

protected:

	Character* _pCharacterAttachedTo;
	
};

#endif