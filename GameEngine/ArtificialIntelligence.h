#ifndef _ARTIFICIALINTELLIGENCE_
#define _ARTIFICIALINTELLIGENCE_

#include "stdafx.h"

class GameObject;
class Character;

class ArtificialIntelligence
{

public:

	ArtificialIntelligence( int areaOfSite );
	~ArtificialIntelligence();

	static const int FINISHEDMOVEPATH = -1;
	static const int MOVEMENTFOLLOW = 0;
	static const int MOVEMENTLINGER = 1;
	static const int MOVEMENTPATHONE = 2;
	static const int MOVEMENTPATHTWO = 3;
	static const int MOVEMENTPATHTHREE = 4;

	virtual void ProccessAI();
	void CollisionStop();

protected:

	int _AreaOfSite;
	int _CurrentWalkPath;
	int _MovementStage;

	GameObject* _GameObject;

	void MovementPathOne();
	void MovementPathTwo();
	void MovementPathThree();
	void MovementLinger();
	void AproachPlayer( Character* player );
};

#endif