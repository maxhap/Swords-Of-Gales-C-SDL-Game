#include"stdafx.h"

Item::Item( int objectID, int x, int y, int width, int height, string spriteLocation ) : Object( objectID, x, y, width, height, spriteLocation )
{
	_pCharacterAttachedTo = NULL;
}

Item::~Item()
{

}

void Item::AttachCharacter( Character* character )
{
	_pCharacterAttachedTo = character;
}

bool Item::Aquire()
{
	return false;
}

InventoryItem* Item::ConvertToInventoryItem()
{
	return NULL;
}