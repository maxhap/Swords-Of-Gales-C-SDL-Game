#include "stdafx.h"

ArtificialIntelligence::ArtificialIntelligence( int areaOfSite )
{
	_AreaOfSite = areaOfSite;
	_CurrentWalkPath = 1;
	_MovementStage = 1;
}

ArtificialIntelligence::~ArtificialIntelligence()
{

}

void ArtificialIntelligence::ProccessAI()
{
	Character* player = GameObjectHolder::instance().GetPlayer();

	int difx = abs( player->Container()->x - _GameObject->Container()->x );
	int dify = abs( player->Container()->y - _GameObject->Container()->y );

	int distnace = (int) sqrt( difx + dify + 0.0 );
	distnace = abs( distnace );

	
	if( distnace <= _AreaOfSite )
	{
		_CurrentWalkPath = ArtificialIntelligence::MOVEMENTFOLLOW; 
		AproachPlayer( player );
	}
	else
	{
		if( _CurrentWalkPath == ArtificialIntelligence::MOVEMENTPATHONE )
		{
			MovementPathOne();
		}
		else if ( _CurrentWalkPath == ArtificialIntelligence::MOVEMENTPATHTWO )
		{
			MovementPathTwo();
		}
		else if ( _CurrentWalkPath == ArtificialIntelligence::MOVEMENTPATHTHREE )
		{
			MovementPathThree();
		}
		else if ( _CurrentWalkPath == ArtificialIntelligence::MOVEMENTLINGER )
		{
			MovementLinger();
		}
		else
		{
			int nextpath = rand() % 4 + 1;

			switch( nextpath )
			{
				case ArtificialIntelligence::MOVEMENTLINGER :  MovementLinger(); break;
				case ArtificialIntelligence::MOVEMENTPATHONE :  MovementPathOne(); break;
				case ArtificialIntelligence::MOVEMENTPATHTWO :  MovementPathTwo(); break;
				case ArtificialIntelligence::MOVEMENTPATHTHREE:  MovementPathThree(); break;
			}	

			_GameObject->SetMoveDirection( GameObject::MOVESTOP );
		}
	}
}

void ArtificialIntelligence::CollisionStop()
{
	_GameObject->SetMoveDirection( GameObject::MOVESTOP );
}

void ArtificialIntelligence::MovementPathOne()
{
	_CurrentWalkPath = ArtificialIntelligence::MOVEMENTPATHONE;

	if( _MovementStage > 0 && _MovementStage < 50 )
	{
		_GameObject->SetMoveDirection( GameObject::MOVEEAST );
		_MovementStage++;
	}
	else if( _MovementStage >= 50 && _MovementStage < 100 )
	{
		_GameObject->SetMoveDirection( GameObject::MOVEWEST );
		_MovementStage++;
	}
	else
	{
		_MovementStage = 1;
		_CurrentWalkPath = ArtificialIntelligence::FINISHEDMOVEPATH;
	}
}

void ArtificialIntelligence::MovementPathTwo()
{
	_CurrentWalkPath = ArtificialIntelligence::MOVEMENTPATHTWO;

	if( _MovementStage > 0 && _MovementStage < 50 )
	{
		_GameObject->SetMoveDirection( GameObject::MOVENORTH );
		_MovementStage++;
	}
	else if( _MovementStage >= 50 && _MovementStage < 100 )
	{
		_GameObject->SetMoveDirection( GameObject::MOVESOUTH );
		_MovementStage++;
	}
	else
	{
		_MovementStage = 1;
		_CurrentWalkPath = ArtificialIntelligence::FINISHEDMOVEPATH;
	}
}	

void ArtificialIntelligence::MovementPathThree()
{
	_CurrentWalkPath = ArtificialIntelligence::MOVEMENTPATHTHREE;

	if( _MovementStage > 0 && _MovementStage < 50 )
	{
		_GameObject->SetMoveDirection( GameObject::MOVENORTH );
		_MovementStage++;
	}
	else if( _MovementStage >= 50 && _MovementStage < 100 )
	{
		_GameObject->SetMoveDirection( GameObject::MOVEEAST );
		_MovementStage++;
	}
	else if( _MovementStage >= 100 && _MovementStage < 150 )
	{
		_GameObject->SetMoveDirection( GameObject::MOVESOUTH );
		_MovementStage++;
	}
	else if( _MovementStage >= 150 && _MovementStage < 200 )
	{
		_GameObject->SetMoveDirection( GameObject::MOVEWEST );
		_MovementStage++;
	}
	else
	{
		_MovementStage = 1;
		_CurrentWalkPath = ArtificialIntelligence::FINISHEDMOVEPATH;
	}
}

void ArtificialIntelligence::MovementLinger()
{
	_CurrentWalkPath = ArtificialIntelligence::MOVEMENTLINGER;

	if( _MovementStage > 0 && _MovementStage < 100 )
	{
		_GameObject->SetMoveDirection( GameObject::MOVESTOP );
		_MovementStage++;
	}
	else
	{
		_MovementStage = 1;
		_CurrentWalkPath = ArtificialIntelligence::FINISHEDMOVEPATH;
	}
}

void ArtificialIntelligence::AproachPlayer( Character* player )
{
	int difx = player->Container()->x - _GameObject->Container()->x;
	int dify = player->Container()->y - _GameObject->Container()->y;


	if( difx >= -2 && difx <= 2 && dify > 0 )
	{
		//movesouth
		_GameObject->SetMoveDirection( GameObject::MOVESOUTH );
	}
	else if( difx >= -2 && difx <= 2 && dify < 0 )
	{
		//movenorth
		_GameObject->SetMoveDirection( GameObject::MOVENORTH );
	}
	else if( difx > 0 && dify >= -2 && dify <= 2 )
	{
		//moveeast
		_GameObject->SetMoveDirection( GameObject::MOVEEAST );
	}
	else if( difx < 0 && dify >= -2 && dify <= 2 )
	{
		//movewest
		_GameObject->SetMoveDirection( GameObject::MOVEWEST );
	}
	else if( difx > 0 && dify > 0 )
	{
		//movesoutheast
		_GameObject->SetMoveDirection( GameObject::MOVESOUTHEAST );
	}
	else if( difx < 0 && dify > 0 )
	{
		//movesouthwest
		_GameObject->SetMoveDirection( GameObject::MOVESOUTHWEST );
	}
	else if( difx < 0 && dify < 0 )
	{
		//movenorthwest
		_GameObject->SetMoveDirection( GameObject::MOVENORTHWEST );
	}
	else if( difx > 0 && dify < 0 )
	{
		//movenortheast
		_GameObject->SetMoveDirection( GameObject::MOVENORTHEAST );
	}

}

