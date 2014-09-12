#include "stdafx.h"

Tile::Tile( int objectType, int number, int x, int y, int width, int height, int tileType, string spriteLocation ) : GameObject( objectType, x, y, width, height , 0, 0, spriteLocation, false )
{
	_TileType = tileType;
	_TileNumber = number;

	_ObjectType = Initialize::Tile;
}

Tile::~Tile()
{	
}

int Tile::GetType() const
{
	return _TileType;
}