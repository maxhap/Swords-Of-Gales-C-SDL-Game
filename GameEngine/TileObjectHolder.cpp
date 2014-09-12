#include "stdafx.h"
#include "stdafx.h"

TileObjectHolder::TileObjectHolder()
{
	_SectorList = new vector<GameSector*>;
}

TileObjectHolder::~TileObjectHolder()
{
	MemoryManagement<GameSector>::instance().CleanVector( _SectorList, true );	
}

void TileObjectHolder::BuildSectors()
{
	int totalSectores = Initialize::SectorDevisionValue * Initialize::SectorDevisionValue;
	int x = 0;
	int y = 0;
	int width = LevelSystem::instance().GetCurrentLevel()->GetContainer()->w / Initialize::SectorDevisionValue;
	int height = LevelSystem::instance().GetCurrentLevel()->GetContainer()->h / Initialize::SectorDevisionValue;

	//Initialize the tiles
    for( int i = 0; i < totalSectores; i++ )
    {       
		GameSector* sector = new GameSector( x, y, width, height );

		_SectorList->insert( _SectorList->end(), 1, sector );

        //Move to next tile spot
        x += width;
        
		int togther = x + width;
		int levWidth = LevelSystem::instance().GetCurrentLevel()->GetContainer()->w;

        //If we've gone too far
        if( togther > levWidth )
        {
            //Move back
            x = 0;
            
            //Move to the next row
            y += height;    
        }
	}
}

vector<GameSector*>* TileObjectHolder::GetAllSectors()
{
	return _SectorList;
}

vector<GameSector*>* TileObjectHolder::GetSectorsContaining( SDL_Rect* rect )
{
	vector<GameSector*>* returnVector = new vector<GameSector*>; 

	for( vector<GameSector*>::iterator i = _SectorList->begin(); i < _SectorList->end(); i++ )
	{
		if( ( *i )->CheckSectorCollision( rect ) )
		{
			returnVector->insert( returnVector->end(), 1, ( *i ) );
		}
	}

	return returnVector;
}

GameSector* TileObjectHolder::GetSectorsContaining( int x, int y )
{
	SDL_Rect rect;
	rect.x = x;
	rect.y = y;
	rect.w = 2;
	rect.h = 2;

	for( vector<GameSector*>::iterator i = _SectorList->begin(); i < _SectorList->end(); i++ )
	{
		if( ( *i )->CheckSectorCollision( &rect ) )
		{
			return ( *i );
		}
	}

	return NULL;
}

void TileObjectHolder::AddSector( GameSector* gameSector )
{
	_SectorList->insert( _SectorList->end(), 1, gameSector ) ;
}

void TileObjectHolder::DeleteSector( GameSector* gameSector )
{
		for( vector<GameSector*>::iterator i = _SectorList->begin(); i < _SectorList->end(); i++ )
		{
			if( ( *i ) == gameSector )
			{
				_SectorList->erase( i );
				break;
			}
		}
}	

bool TileObjectHolder::LoadAllObjectSprites()
{
	for( vector<GameSector*>::iterator i = _SectorList->begin(); i < _SectorList->end(); i++ )
	{
		vector<GameObject*>* objects = ( *i )->GetAll();

		for( vector<GameObject*>::iterator z = objects->begin(); z < objects->end(); z++ )
		{
			if( ( *z )->LoadItemImage() == false )
			{
				return false;
			}
		}
		
	}

	return true;
}

void TileObjectHolder::AddObjectToReleventSectors( GameObject* object )
{
	if( object == NULL ) 
	{
		return;
	}

	vector<GameSector*>* secList = GetSectorsContaining( object->Container() );

	for( vector<GameSector*>::iterator i = secList->begin(); i < secList->end(); i++ )
	{
		( *i )->Add( object );
	}

	MemoryManagement<GameSector>::instance().CleanVector( secList, false );
}

void TileObjectHolder::RemoveObjectFromReleventSectors( GameObject* object )
{
	if( object == NULL ) 
	{
		return;
	}

	vector<GameSector*>* secList = GetSectorsContaining( object->Container() );

	for( vector<GameSector*>::iterator i = secList->begin(); i < secList->end(); i++ )
	{
		( *i )->Remove( object );
	}

	MemoryManagement<GameSector>::instance().CleanVector( secList, false );
}	

int TileObjectHolder::NumberOfSectoresObjectContainedIn( GameObject* object )
{
	int counter = 0;

	for( vector<GameSector*>::iterator i = _SectorList->begin(); i < _SectorList->end(); i++ )
	{
		vector<GameObject*>* objects = ( *i )->GetAll();

		for( vector<GameObject*>::iterator z = objects->begin(); z < objects->end(); z++ )
		{
			if (  ( *z ) == object )
			{
				counter++;
				break;
			}
		}	
	}

	return counter;	
}

void TileObjectHolder::DestroySectors()
{
	for( vector<GameSector*>::iterator i = _SectorList->begin(); i < _SectorList->end(); i++ )
	{
		vector<GameObject*>* objectList = ( *i )->GetAll();

		for( vector<GameObject*>::iterator z = objectList->begin(); z < objectList->end(); z++ )
		{
			if( NumberOfSectoresObjectContainedIn( *z ) <= 1 )
			{
				delete ( *z );
			}
		}

		objectList->erase( objectList->begin(), objectList->end() );
	}

	MemoryManagement<GameSector>::instance().EmptyVector( _SectorList, true );
}
