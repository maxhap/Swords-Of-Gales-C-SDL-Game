#ifndef _TILEHOLDER_
#define _TILEHOLDER_

#include "stdafx.h"
#include "MemoryManagement.h"

class Tile; 

class TileObjectHolder : public Singleton<TileObjectHolder>
{

public:

	~TileObjectHolder();

	vector<GameSector*>* GetAllSectors();
	vector<GameSector*>* GetSectorsContaining( SDL_Rect* rect );
	
	GameSector* GetSectorsContaining( int x, int y );

	void AddSector( GameSector* gameSector );
	void DeleteSector( GameSector* gameSector );
	void AddObjectToReleventSectors( GameObject* object );
	void RemoveObjectFromReleventSectors( GameObject* object );
	void DestroySectors();
	void BuildSectors();

	int NumberOfSectoresObjectContainedIn( GameObject* object );

	bool LoadAllObjectSprites();	

private:

	friend class Singleton<TileObjectHolder>;
	TileObjectHolder();

	vector<GameSector*>* _SectorList;
};


#endif