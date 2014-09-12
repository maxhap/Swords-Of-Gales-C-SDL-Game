#ifndef _INTERACTABLE_
#define _INTERACTABLE_

#include "stdafx.h"

class Interactable
{

public :
	
	Interactable( int x, int y, int width, int height );
	~Interactable();

	void SetInteraction( int objectID, bool interact );

	virtual void Interact();

	bool GetSomethingToIntercatWith();	

	int GetLastInteractID(); 

protected:

	int _LastInteractID;

	bool _SomethingToInteractWith;
	
	SDL_Rect* _pInteractionRadious;

};

#endif
