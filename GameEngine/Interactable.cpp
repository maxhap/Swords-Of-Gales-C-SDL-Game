#include "stdafx.h"

Interactable::Interactable( int x, int y, int width, int height )
{
	_SomethingToInteractWith = false;
	_LastInteractID = -1;

	_pInteractionRadious = new SDL_Rect();

	_pInteractionRadious->x = x;
	_pInteractionRadious->y = y;
	_pInteractionRadious->w = width;
	_pInteractionRadious->h = height;
}

Interactable::~Interactable()
{
	delete _pInteractionRadious;
}

void Interactable::SetInteraction( int objectID, bool interact )
{
	if( interact == false && _SomethingToInteractWith == true)
	{
		if( objectID ==	_LastInteractID )
		{
			_SomethingToInteractWith = false;
		}
	}
	else
	{
		if( interact == true )
		{
			_LastInteractID = objectID;
			_SomethingToInteractWith = true;
		}
		else
		{
			_SomethingToInteractWith = false;
		}
	}
}

bool Interactable::GetSomethingToIntercatWith()
{
	return _SomethingToInteractWith;
}

int Interactable::GetLastInteractID()
{
	return _LastInteractID;
}

void Interactable::Interact()
{
	ErrorSystem::instance().WriteError( "Interaction called but no override given" );
}