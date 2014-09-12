#include "stdafx.h"

using namespace std;

InventorySystem::InventorySystem( int x, int y, int width, int height, string backgroundImageLocation, string activeImageLocation, int maxInventorySpace, int inventoryItemWidth, int inventoryItemHeight ) : InventoryHolder( x, y, width, height, backgroundImageLocation, activeImageLocation )
{
	_MaxInventorySpace = maxInventorySpace;
	
	_pCurrentTogledAttackItem = NULL;
	_pPlayer = NULL;

	_InventoryItemWidth = inventoryItemWidth;
	_InventoryItemHeight = inventoryItemHeight;
}

InventorySystem::~InventorySystem()
{

}

void InventorySystem::AddPlayer( Player* player )
{
	_pPlayer = player;	
}

void InventorySystem::HandleInput( SDL_Event event )
{
	if( event.type == SDL_KEYUP )
	{
		switch( event.key.keysym.sym )
		{
			case SDLK_1: UseInventoryItem( 0 ); break;
			case SDLK_2: UseInventoryItem( 1 ); break;
			case SDLK_3: UseInventoryItem( 2 ); break;
			case SDLK_4: UseInventoryItem( 3 ); break;
			case SDLK_5: UseInventoryItem( 4 ); break;
			case SDLK_6: UseInventoryItem( 5 ); break;
			case SDLK_7: UseInventoryItem( 6 ); break;
			case SDLK_8: UseInventoryItem( 7 ); break;
			case SDLK_9: UseInventoryItem( 8 ); break;
			case SDLK_0: UseInventoryItem( 9 ); break;
		}
	}
}

bool  InventorySystem::AddInventoryItem( InventoryItem* item )
{
	_pPlayer->AddItem( item );
	return true;
}

void InventorySystem::UseInventoryItem( int itemNumber )
{
	int pos = 0;

	//character attacks
	vector<Attack*>* attackList = _pPlayer->GetAttackList();
	
	for( vector<Attack*>::iterator i = attackList->begin(); i != attackList->end(); i++ )
	{
		if( pos == itemNumber )
		{
			if ( ( *i )->GetIsTogle() == true )
			{
				if( ( *i ) != _pCurrentTogledAttackItem )
				{
					DisableAllTogles();
					_pCurrentTogledAttackItem  = ( *i );
				}

				( *i )->InventoryUse();
			}
			else
			{
				( *i )->InventoryUse();
				delete *i;

				attackList->erase( attackList->begin() + pos );
				break;
			}

			return;
		}

		pos++;
	}

	//cyn item number to inventory vector ( items come after attacks )
	itemNumber -= pos;

	//Inventory Items
	vector<InventoryItem*>* list = _pPlayer->GetInventoryList();

	int vectorPossition = 0;
	InventoryItem* foundItem = NULL;

	for( vector<InventoryItem*>::iterator i = list->begin(); i != list->end(); i++, vectorPossition++ )
	{
		if( vectorPossition == itemNumber )
		{
			foundItem = ( *i );
			break;
		}		
	}

	if( foundItem != NULL )
	{
		foundItem->InventoryUse();
		_pPlayer->RemoveItem( foundItem );

		delete foundItem;
	}
}

void InventorySystem::DisableAllTogles()
{

	//character attacks
	vector<Attack*>* attackList = _pPlayer->GetAttackList();
	
	for( vector<Attack*>::iterator i = attackList->begin(); i != attackList->end(); i++ )
	{
		if( ( *i )->GetIsTogle() == true )
		{
			( *i )->SetActive( false );	
		}
	}
}

void InventorySystem::DrawInventoryItems( MainWnd* window )
{
	int x = _pInventoryContainer->x;
	int y = _pInventoryContainer->y;

	//character attacks
	vector<Attack*>* attackList = _pPlayer->GetAttackList();
	
	for( vector<Attack*>::iterator i = attackList->begin(); i != attackList->end(); i++ )
	{
		if( ( *i )->GetActive() )
		{
			SDL_Rect position;
			position.x = x - 20;
			position.y = y;
			position.h = _InventoryItemHeight;
			position.w = _InventoryItemWidth;

			( *i )->DrawInInventory( window,  position );

			if( x + _InventoryItemWidth > _pInventoryContainer->w )
			{
				y += _InventoryItemHeight;
				x = _pInventoryContainer->x;
			}
			else
			{
				x += _InventoryItemWidth;
			}
		}
	}

	//Inventory Items
	//now limited to 4 items so center images
	vector<InventoryItem*>* list = _pPlayer->GetInventoryList();

	if( list->size() == 1 )
	{
		x = 350;
	}
	else if( list->size() == 2 )
	{
		x = 310;
	}
	else if( list->size() == 3 )
	{
		x = 260;
	}
	else
	{
		x = 220;
	}



	for( vector<InventoryItem*>::iterator i = list->begin(); i != list->end(); i++ )
	{
		SDL_Rect position;
		position.x = x;
		position.y = y;
		position.h = _InventoryItemHeight;
		position.w = _InventoryItemWidth;

		( *i )->DrawInInventory( window,  position );

		if( x + _InventoryItemWidth > _pInventoryContainer->w )
		{
			y += _InventoryItemHeight;
			x = _pInventoryContainer->x;
		}
		else
		{
			x += _InventoryItemWidth;
		}		
	}

}