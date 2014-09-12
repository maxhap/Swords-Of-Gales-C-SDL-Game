#ifndef _SWORDATTACK_
#define _SWORDATTACK_

class SwordAttackInventoryItem : public InventoryItem
{

public:

	SwordAttackInventoryItem( bool isTogle, string backgroundImageLocation, string activeImageLocation );
	~SwordAttackInventoryItem();

	void Use();

private:

};


#endif