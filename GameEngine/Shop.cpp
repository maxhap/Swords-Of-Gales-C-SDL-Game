#include "stdafx.h"

Shop::Shop( int objectID, int x, int y, int width, int height, string backgroundImageLocation ) : Object( objectID, x, y, width, height, backgroundImageLocation )
{
	_pItemList = new vector<ShopItem*>;
	_Empty = true;
}

Shop::~Shop()
{
	MemoryManagement<ShopItem>::instance().CleanVector( _pItemList, true );
}

void Shop::Draw( MainWnd* window, Camora* camora )
{
	window->RenderToScreen( _pSprite, _Container,  NULL );

	for( vector<ShopItem*>::iterator i = _pItemList->begin(); i < _pItemList->end(); i++ )
	{
		( *i )->Draw( window, camora );
	}
}

void Shop::AddItem( ShopItem* item )
{
	_pItemList->insert( _pItemList->end(), 1, item );

	if( _Empty )
	{
		_Empty = false;
		item->SetIsSelected( true );
	}
	else
	{
		item->SetIsSelected( false );
	}
}

void Shop::HandleInput( SDL_Event passedEvent )
{
	if( passedEvent.type == SDL_KEYUP )
	{
		SDLKey key = passedEvent.key.keysym.sym;

		if( key == SDLK_UP || key == SDLK_DOWN )
		{	
			for( vector<ShopItem*>::iterator i = _pItemList->begin(); i < _pItemList->end(); i++ )
			{
				if( ( *i )->GetIsSelected() )
				{	
					if( key == SDLK_UP && i != _pItemList->begin() )
					{
						( *i )->SetIsSelected( false );
						i--;
						( *i )->SetIsSelected( true );
					}

					else if( key == SDLK_DOWN && i != _pItemList->end() -1 )
					{
						( *i )->SetIsSelected( false );
						i++;
						( *i )->SetIsSelected( true );
					}
				}
			}
		}
		else if( key == SDLK_SPACE )
		{
			for( vector<ShopItem*>::iterator i = _pItemList->begin(); i < _pItemList->end(); i++ )
			{
				if( ( *i )->GetIsSelected() )
				{	
					( *i )->Buy();
				}
			}
		}
	}
}