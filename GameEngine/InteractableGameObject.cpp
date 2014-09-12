#include "stdafx.h"

InteractableGameObject::InteractableGameObject( int objectID, int x, int y, int width, int height, int startingAngle, int movementSpeed, string spriteLocation, bool isHittable, int interactionX, int interactionY, int interactionWidth, int interactionHeight ) : GameObject( objectID, x, y, width, height, startingAngle, movementSpeed, spriteLocation, isHittable ), Interactable( interactionX, interactionY, interactionWidth, interactionHeight ) 
{
	_IsInteractable = true;
}

InteractableGameObject::~InteractableGameObject()
{

}

bool InteractableGameObject::WithinInteractionRange( InteractableGameObject* otherObject )
{
	//tempoarily change container to fit interaction range
	int tmpX = _Container->x;
	int tmpY = _Container->y;
	int tmpW = _Container->w; 
	int tmpH = _Container->h;

	_Container->x = _pInteractionRadious->x;
	_Container->y = _pInteractionRadious->y;
	_Container->w = _pInteractionRadious->w;
	_Container->h = _pInteractionRadious->h;

	bool withinRange = HasColidedRect( otherObject->Container() );

	otherObject->SetInteraction( _ObjectID, withinRange );

	//change container back
	_Container->x = tmpX;
	_Container->y = tmpY;
	_Container->w = tmpW;
	_Container->h = tmpH;

	return withinRange;
}

void InteractableGameObject::InitiateInteraction()
{
	if( _SomethingToInteractWith )
	{
		GameObject* go = GameObjectHolder::instance().GetObjectWithID( _LastInteractID );

		//case safe because only IGO could set id
		InteractableGameObject* igo = ( InteractableGameObject* ) go;

		igo->Interact();
	}
}