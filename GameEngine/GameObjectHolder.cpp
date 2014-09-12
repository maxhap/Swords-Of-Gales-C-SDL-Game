#include "stdafx.h"

GameObjectHolder::GameObjectHolder()
{
	_SectorList = new vector<GameSector*>;
	_pGameObjetContainerEntities = new vector<GameObject*>;
	_pGameObjetContainerBlockers = new vector<GameObject*>;
	_pGameItemContainer = new vector<Item*>;
	_pPlayer1 = NULL;
}

GameObjectHolder::~GameObjectHolder()
{
	MemoryManagement<GameSector>::instance().CleanVector( _SectorList, false );
	MemoryManagement<GameObject>::instance().CleanVector( _pGameObjetContainerEntities, true);
	MemoryManagement<GameObject>::instance().CleanVector( _pGameObjetContainerBlockers, true);
	cout << "Floor item  size = " << _pGameItemContainer->size();
	MemoryManagement<Item>::instance().CleanVector( _pGameItemContainer, true);
	
	delete _pPlayer1;
}

void GameObjectHolder::BuildSectors()
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

vector<GameSector*>* GameObjectHolder::GetAllSectors()
{
	return _SectorList;
}

vector<GameSector*>* GameObjectHolder::GetSectorsContaining( SDL_Rect* rect )
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

vector<GameSector*>* GameObjectHolder::GetSectorsContaining( GameObject* object )
{
	vector<GameSector*>* returnVector = new vector<GameSector*>; 

	for( vector<GameSector*>::iterator i = _SectorList->begin(); i < _SectorList->end(); i++ )
	{
		if( ( *i )->ObjectIsContained( object ) )
		{
			returnVector->insert( returnVector->end(), 1, ( *i ) );
		}
	}

	return returnVector;
}

GameSector* GameObjectHolder::GetSectorsContaining( int x, int y )
{
	SDL_Rect rect;
	rect.x = x;
	rect.y = y;
	rect.w = 1;
	rect.h = 1;

	for( vector<GameSector*>::iterator i = _SectorList->begin(); i < _SectorList->end(); i++ )
	{
		if( ( *i )->CheckSectorCollision( &rect ) )
		{
			return ( *i );
		}
	}

	return NULL;
}

void GameObjectHolder::AddSector( GameSector* gameSector )
{
	_SectorList->insert( _SectorList->end(), 1, gameSector ) ;
}

void GameObjectHolder::DeleteSector( GameSector* gameSector )
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

Player* GameObjectHolder::GetPlayer()
{
 	if( _pPlayer1 == NULL )
	{
		ErrorSystem::instance().WriteError( "Player is NULL" );
	}

	return _pPlayer1;
}

void GameObjectHolder::AddPlayer( Player* player )
{
	_pPlayer1 = player;
}

bool GameObjectHolder::LoadAllObjectSprites()
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

void GameObjectHolder::AddObjectToReleventSectors( GameObject* object )
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

void GameObjectHolder::RemoveObjectFromReleventSectors( GameObject* object )
{
	if( object == NULL ) 
	{
		return;
	}

	vector<GameSector*>* secList = GetSectorsContaining( object );

	for( vector<GameSector*>::iterator i = secList->begin(); i < secList->end(); i++ )
	{
		( *i )->Remove( object );
	}

	MemoryManagement<GameSector>::instance().CleanVector( secList, false );
}

void GameObjectHolder::RemoveObjectFromAllSectors( GameObject* object )
{
	if( object == NULL ) 
	{
		return;
	}

	vector<GameSector*>* secList = GetSectorsContaining( object );

	for( vector<GameSector*>::iterator i = secList->begin(); i < secList->end(); i++ )
	{
		( *i )->Remove( object );
	}

	MemoryManagement<GameSector>::instance().CleanVector( secList, false );
}	

int GameObjectHolder::NumberOfSectoresObjectContainedIn( GameObject* object )
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

void GameObjectHolder::DestroySectors()
{
	for( vector<GameSector*>::iterator i = _SectorList->begin(); i < _SectorList->end(); i++ )
	{
		vector<GameObject*>* objectList = ( *i )->GetAll();

		for( vector<GameObject*>::iterator z = objectList->begin(); z < objectList->end(); z++ )
		{
			if( NumberOfSectoresObjectContainedIn( *z ) <= 1 )
			{
				//delete ( *z );
			}
		}

		objectList->erase( objectList->begin(), objectList->end() );
	}

	MemoryManagement<GameSector>::instance().EmptyVector( _SectorList, true );
}

vector<GameObject*>* GameObjectHolder::GetGameEntityContainer() const
{
	return _pGameObjetContainerEntities;
}

void GameObjectHolder::AddToEntityContainer( GameObject* object)
{
	_pGameObjetContainerEntities->insert( _pGameObjetContainerEntities->end(), 1, object ); 
}

vector<GameObject*>* GameObjectHolder::GetGameBlockerContainer() const
{
	return _pGameObjetContainerBlockers;
}

void GameObjectHolder::AddToBlockerContainer( GameObject* object)
{
	_pGameObjetContainerBlockers->insert( _pGameObjetContainerBlockers->end(), 1, object ); 
}

void GameObjectHolder::EmptyContainer()
{
	MemoryManagement<GameObject>::instance().EmptyVector( _pGameObjetContainerEntities, false );
	MemoryManagement<GameObject>::instance().EmptyVector( _pGameObjetContainerBlockers, false );
}

void GameObjectHolder::EmptyItemContainer()
{
	MemoryManagement<Item>::instance().EmptyVector( _pGameItemContainer, false );
}

void GameObjectHolder::RemoveFromGameContainer( GameObject* object )
{	
	bool erased = false;
	vector<GameObject*>::iterator iter = find( _pGameObjetContainerEntities->begin(), _pGameObjetContainerEntities->end(), object );

	if( iter != _pGameObjetContainerEntities->end() )
	{
		_pGameObjetContainerEntities->erase( iter ); 
		erased = true;
	}

	if( !erased )
	{
		vector<GameObject*>::iterator iter = find( _pGameObjetContainerBlockers->begin(), _pGameObjetContainerBlockers->end(), object );

		if( iter != _pGameObjetContainerBlockers->end() )
		{
			_pGameObjetContainerBlockers->erase( iter ); 
			erased = true;
		}
	}
}

void GameObjectHolder::HandleSectorMovement( GameObject* object )
{
	RemoveObjectFromReleventSectors( object );
	AddObjectToReleventSectors( object );
}

void GameObjectHolder::AddToItemContainer( Item* item )
{
	_pGameItemContainer->insert( _pGameItemContainer->end(), 1, item );
}

void GameObjectHolder::RemoveFromItemContainer( Item* item )
{
	vector<Item*>::iterator iter = find( _pGameItemContainer->begin(), _pGameItemContainer->end(), item );

	if( iter != _pGameItemContainer->end() )
	{
		_pGameItemContainer->erase( iter ); 
	}
}

vector<Item*>* GameObjectHolder::GetGameItemContainer() const
{
	return _pGameItemContainer;
}

Beacon* GameObjectHolder::FindBeacon( string ID )
{
	for( vector<GameObject*>::iterator i = _pGameObjetContainerEntities->begin(); i != _pGameObjetContainerEntities->end(); i++ )
	{
		if( ( *i )->GetObjectType() == Initialize::Beacon )
		{
			Beacon* beacon = ( Beacon* ) ( *i );

			if( beacon->GetEntryPointID() == ID )
			{
				return beacon;
			}
		}
	}

	return NULL;
}

GameObject* GameObjectHolder::GetObjectWithID( int id )
{
	for( vector<GameObject*>::iterator i = _pGameObjetContainerEntities->begin(); i != _pGameObjetContainerEntities->end(); i++ )
	{
		if( ( *i )->GetID() == id )
		{
			return ( *i );
		}
	}

	return NULL;
}
