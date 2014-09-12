#ifndef _ITEMHANDLER_
#define _ITEMHANDLER_

#include "stdafx.h"

class ItemHandler: public Singleton<ItemHandler>
{

public:

	~ItemHandler();

	void AddRandomItem( int group, int x, int y );

private:

	friend class Singleton<ItemHandler>;
	ItemHandler();
	
};

#endif