#ifndef _INTERACTABLEGAMEOBJECT_
#define _INTERACTABLEGAMEOBJECT_

#include "stdafx.h"

class InteractableGameObject : public GameObject, public Interactable
{

public:

	InteractableGameObject( int objectID, int x, int y, int width, int height, int startingAngle, int movementSpeed, string spriteLocation, bool isHittable, int interactionX, int interactionY, int interactionWidth, int interactionHeight );
	~InteractableGameObject();

	bool WithinInteractionRange( InteractableGameObject* otherObject );

	void InitiateInteraction();

private:	


};

#endif