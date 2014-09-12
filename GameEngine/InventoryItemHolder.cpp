#include "stdafx.h"

InventoryItemHolder::InventoryItemHolder()
{
	_pItemList = new vector<InventoryItem*>;
}

InventoryItemHolder::~InventoryItemHolder()
{
	DeleteInventoryItems();
	delete _pItemList;
}

void InventoryItemHolder::DeleteInventoryItems()
{
	cout << "Inventory size = " << _pItemList->size();

	for( vector<InventoryItem*>::iterator i = _pItemList->begin(); i != _pItemList->end(); i++ )
	{
		delete ( *i );
	}

	_pItemList->erase( _pItemList->begin(), _pItemList->end() );
}

void InventoryItemHolder::AddItem( InventoryItem* item )
{
	_pItemList->insert( _pItemList->end(), 1, item );
}

vector<InventoryItem*>* InventoryItemHolder::GetInventoryList()
{
	return _pItemList;
}

void InventoryItemHolder::RemoveItem( InventoryItem* item )
{
	vector<InventoryItem*>::iterator iter = find( _pItemList->begin(), _pItemList->end(), item );

	if( iter != _pItemList->end() )
	{
		_pItemList->erase( iter ); 
	}	
}