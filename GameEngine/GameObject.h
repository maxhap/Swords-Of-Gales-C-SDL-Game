#ifndef _GameObject_
#define _GameObject_

#include "stdafx.h"

class GameObject : public Object, public Hittable
{

public:

	static const int MOVESTOP = 0;
	static const int MOVENORTH = 1;
	static const int MOVENORTHEAST = 2;
	static const int MOVEEAST = 3;
	static const int MOVESOUTHEAST = 4;
	static const int MOVESOUTH = 5;
	static const int MOVESOUTHWEST = 6;
	static const int MOVEWEST = 7;
	static const int MOVENORTHWEST = 8;

	GameObject( int objectID, int x, int y, int width, int height, int startingAngle, int movementSpeed, string spriteLocation, bool isHittable );
	~GameObject();

	bool GetIsAnimating();
	bool GetIsIntelligent() const;
	bool GetMovable();
	bool GetIsInteractable();

	virtual bool Update( bool nocollision, bool includeAI = false  );
	
	virtual void HandleInput( SDL_Event passedEvent );	

	void DrawTestRect( MainWnd* window, Camora* camora );
	void UpdateVelocity( int xVelIncrease, int yVelIncrease ); 

	void UpadetCamora( Camora* camora, SDL_Rect* levelBoudories );
	void SwordAttackAnimation();
	void BowArrowAnimation();
	void SetMoveDirection( int moveNumber );
	void SetVelocity( int xVel, int yVel );
	void SetMovable( bool movable );
	
	int GetXVelocity();
	int GetYVeloctiy();
	int GetDirection();
	int GetMoveDirection();
	int GetObjectType();
	int GetEntityType();

protected:

	bool _IsAnimating;
	bool _IsCreatable;
	bool _IsIntelligent;
	bool _IsInteractable;
	bool _Movable;
	bool _KeyDown;	

	int _EntityType;
	int _Key;
	int _MovementSpeed;
	int _CurrentMovementSpeed;
	int _VelocityX;
	int _VelocityY;
	int _RotationAngle;
	int _CurrentRotationSpeed;
	int _AnimationRate;
	int _AnimationCycle;
	int _TmpAnimationRate;
	int _CurrentAnimation;
	int _MoveDirection;
	int _CurrentAnimationDirection;
	int _AnimationDirection;

	void UpdateMovement( bool noCollision );
	void ProcessAnimation( bool nocollision );
	
	void UpdateWalkSprite( bool noCollision );
	void UpdateSwordSprite();
	void UpdateBowArrowSprite();
	void ResetSpriteX();
};


#endif