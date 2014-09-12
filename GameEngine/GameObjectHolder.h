#ifndef _GAMEHOLDER_
#define _GAMEHOLDER_

#include "stdafx.h"
#include "MemoryManagement.h"

class GameObject;
class Character; 
class GameSector;
class Item;
class Beacon;
class Player;

class GameObjectHolder: public Singleton<GameObjectHolder>
{

public:

	~GameObjectHolder();

	vector<GameSector*>* GetAllSectors();
	vector<GameSector*>* GetSectorsContaining( SDL_Rect* rect );
	vector<GameSector*>* GetSectorsContaining( GameObject* object );
	GameSector* GetSectorsContaining( int x, int y );
	vector<GameObject*>* GetGameEntityContainer() const;
	vector<GameObject*>* GetGameBlockerContainer() const;
	vector<Item*>* GetGameItemContainer() const;

	Player* GetPlayer();

	void AddSector( GameSector* gameSector );
	void DeleteSector( GameSector* gameSector );
	void AddPlayer( Player* player );
	void AddObjectToReleventSectors( GameObject* object );
	void RemoveObjectFromReleventSectors( GameObject* object );
	void DestroySectors();
	void AddToEntityContainer( GameObject* object);
	void AddToBlockerContainer( GameObject* object);
	void EmptyContainer();
	void EmptyItemContainer();
	void RemoveFromGameContainer( GameObject* object );
	void HandleSectorMovement( GameObject* object );
	void RemoveObjectFromAllSectors( GameObject* object );
	void AddToItemContainer( Item* item );
	void RemoveFromItemContainer( Item* item );
	void BuildSectors();

	bool LoadAllObjectSprites();	

	int NumberOfSectoresObjectContainedIn( GameObject* object );

	Beacon* FindBeacon( string ID );

	GameObject* GetObjectWithID( int id );

private:

	friend class Singleton<GameObjectHolder>;
	GameObjectHolder();

	vector<GameSector*>* _SectorList;
	vector<GameObject*>* _pGameObjetContainerEntities;
	vector<GameObject*>* _pGameObjetContainerBlockers;
	vector<Item*>* _pGameItemContainer;

	Player* _pPlayer1;
};


#endif