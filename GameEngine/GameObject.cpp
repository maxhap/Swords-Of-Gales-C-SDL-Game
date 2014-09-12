#include "stdafx.h"

using namespace std;

GameObject::GameObject( int objectID, int x, int y, int width, int height, int startingAngle, int movementSpeed, string spriteLocation, bool isHittable ) : Hittable( isHittable ), Object( objectID, x, y, width, height, spriteLocation )
{
	_ObjectType = Initialize::Unset;
	_EntityType = Initialize::Entity;

	_IsAnimating = false;
	_IsCreatable = true;
	_IsIntelligent = false;

	_VelocityX = 0;
	_VelocityY = 0;
	_MoveDirection = 0;

	_RotationAngle = startingAngle;
	_MovementSpeed = movementSpeed;
	_CurrentMovementSpeed = 0;
	_CurrentRotationSpeed = 0;
	_AnimationRate = Initialize::RunAnimationRate;
	_AnimationCycle = 0;
	_CurrentAnimation = Initialize::AnimationRun;
	_CurrentSpritePossitionY = 0;

	_Movable = true;
	_CurrentAnimationDirection = 0;
	_AnimationDirection = 0;

	_IsInteractable = false;
}

GameObject::~GameObject()
{
}

void GameObject::DrawTestRect( MainWnd* window, Camora* camora )
{
	if( window->GetRenderMode() == MainWnd::SDL_RENDER )
	{
		//only draw if in viewing range
		if( _Container->x + _Container->w + 50 < ( camora->GetRect()->x + camora->GetRect()->w ) && 
			_Container->y + _Container->h + 50 < ( camora->GetRect()->y + camora->GetRect()->h ) &&
			( _Container->x ) > camora->GetRect()->x &&
			( _Container->y ) > camora->GetRect()->y )
		{
			//box
			Draw_Rect( window->GetSurface(), _Container->x - camora->GetRect()->x, _Container->y - camora->GetRect()->y, ( _Container->w ), ( _Container->h ), SDL_MapRGB( window->GetSurface()->format, 120, 255, 133 ) );
		}

		//only draw if in viewing range
		if( _Container->x + _Container->w +50 < ( camora->GetRect()->x + camora->GetRect()->w - 10 ) && 
			_Container->y + _Container->h + 50 < ( camora->GetRect()->y + camora->GetRect()->h  - 10) &&
			( _Container->x ) > camora->GetRect()->x + 40 &&
			( _Container->y ) > camora->GetRect()->y + 40 )
		{
				//circe for visual angle
				Draw_Circle( window->GetSurface(), ( _Container->x + _Container->w / 2 ) - camora->GetRect()->x, ( _Container->y + _Container->h / 2 ) - camora->GetRect()->y, 50, SDL_MapRGB( window->GetSurface()->format, 220, 213, 330 )  );

				//triganomerty for direction line
				int lineStartX = _Container->x + ( _Container->w / 2 );		
				int lineStartY = _Container->y + ( _Container->h / 2 );

				//triganomatry maths
				int lineEndX = int ( cos( ( GetDirection() + 0.0 ) * M_PI / 180.0 ) * 50 );
				int lineEndY = int ( sin( ( GetDirection() + 0.0 ) * M_PI / 180.0 ) * 50 );

				lineEndX += lineStartX;
				lineEndY += lineStartY;
			
				Draw_Line( window->GetSurface(), lineStartX - camora->GetRect()->x, lineStartY - camora->GetRect()->y, lineEndX - camora->GetRect()->x, lineEndY - camora->GetRect()->y, SDL_MapRGB( window->GetSurface()->format, 255, 0, 0 ) );					
		}
	}
}

void GameObject::HandleInput( SDL_Event passedEvent )
{
	//compase movement
	if( Initialize::CurrentMovementType == Initialize::CompasMovement )
	{
		if( passedEvent.type == SDL_KEYDOWN )
		{
			if( passedEvent.key.keysym.sym == SDLK_DOWN )
			{
				//_VelocityY += _MovementSpeed;
				_RotationAngle = 90;
				_AnimationDirection = Initialize::SpriteDownMotion;
			}
		
			else if( passedEvent.key.keysym.sym == SDLK_UP )
			{
				//_VelocityY -= _MovementSpeed;
				_RotationAngle = 270;
				_AnimationDirection = Initialize::SpriteUpMotion;
			}
		
			else if( passedEvent.key.keysym.sym == SDLK_RIGHT )
			{
				//_VelocityX += _MovementSpeed;
				_RotationAngle = 0;
				_AnimationDirection = Initialize::SpriteRightMotion;
			}
		
			else if( passedEvent.key.keysym.sym == SDLK_LEFT )
			{
				//_VelocityX -= _MovementSpeed;
				_RotationAngle = 180;
				_AnimationDirection = Initialize::SpriteLeftMotion;
			}

			_VelocityX = ( int )( cos( ( _RotationAngle + 0.0 ) * M_PI / 180.0 ) * _MovementSpeed );
			_VelocityY = ( int )( sin( ( _RotationAngle + 0.0 ) * M_PI / 180.0 ) * _MovementSpeed );
		}

		else if( passedEvent.type == SDL_KEYUP )
		{
			if( passedEvent.key.keysym.sym == SDLK_DOWN )
			{
				_VelocityY = 0;
			}
		
			else if( passedEvent.key.keysym.sym == SDLK_UP )
			{
				_VelocityY = 0;
			}
		
			else if( passedEvent.key.keysym.sym == SDLK_RIGHT )
			{
				_VelocityX = 0;
			}
		
			else if( passedEvent.key.keysym.sym == SDLK_LEFT )
			{
				_VelocityX = 0;
			}
		}
	}

	//roatation movement
	else if( Initialize::CurrentMovementType == Initialize::RotationMovement )
	{
		if( passedEvent.type == SDL_KEYDOWN )
		{
			if( passedEvent.key.keysym.sym == SDLK_DOWN )
			{
				_CurrentMovementSpeed -= _MovementSpeed;
			}
		
			if( passedEvent.key.keysym.sym == SDLK_UP )
			{
				_CurrentMovementSpeed += _MovementSpeed;
			}
		
			if( passedEvent.key.keysym.sym == SDLK_RIGHT )
			{
				_CurrentRotationSpeed += Initialize::RotationSpeed;
			}
		
			if( passedEvent.key.keysym.sym == SDLK_LEFT )
			{
				_CurrentRotationSpeed -= Initialize::RotationSpeed;
			}
		}

		if( passedEvent.type == SDL_KEYUP )
		{
			if( passedEvent.key.keysym.sym == SDLK_DOWN )
			{
				_CurrentMovementSpeed = 0;
			}
		
			if( passedEvent.key.keysym.sym == SDLK_UP )
			{
				_CurrentMovementSpeed = 0;
			}
		
			if( passedEvent.key.keysym.sym == SDLK_RIGHT )
			{
				_CurrentRotationSpeed = 0;
			}
		
			if( passedEvent.key.keysym.sym == SDLK_LEFT )
			{
				_CurrentRotationSpeed = 0;
			}
		}
	}
}

bool GameObject::Update( bool nocollision, bool includeAI )
{
	if( !_IsCreatable )
	{
		return false;
	}

	ProcessAnimation( nocollision );
	UpdateMovement( nocollision );

	return true;
}

void GameObject::ProcessAnimation( bool nocollision )
{
	//animation
	if( nocollision )
	{
		//check for change in direction while animating
		if( _CurrentAnimationDirection != _AnimationDirection )
		{
			_CurrentAnimationDirection = _AnimationDirection;
			_CurrentAnimation = Initialize::AnimationRun;
			_AnimationRate = Initialize::RunAnimationRate;
			_IsAnimating = false;
			_AnimationCycle = _AnimationRate;
			_CurrentSpritePossitionX = 0;
		}

		if( _AnimationCycle >= _AnimationRate )
		{
			if( _CurrentAnimation == Initialize::AnimationRun )
			{
				UpdateWalkSprite( nocollision );
			}
			else if( _CurrentAnimation == Initialize::AnimationSwordAttack )
			{
				UpdateSwordSprite();
			}
			else if( _CurrentAnimation == Initialize::AnimationBowArrow )
			{
				UpdateBowArrowSprite();
			}

			_AnimationCycle = 0;
		}
		else
		{
			_AnimationCycle++;
		}
	}
	else
	{
		//reset sprite to stop
		_AnimationCycle = 0;
		_pSpriteClip->x = 0;
	}
}

void GameObject::UpdateMovement( bool noCollision )
{
		//roatation movement
	if( Initialize::CurrentMovementType == Initialize::RotationMovement && noCollision == true )
	{
		//rotation increase
		_RotationAngle += _CurrentRotationSpeed;
		
		if( _RotationAngle >= 360 )
		{
			_RotationAngle = _RotationAngle - 360;
		}

		if( _RotationAngle <= 0 )
		{
			_RotationAngle = 360 + _RotationAngle;
		}

		//triganomatry maths
		_VelocityX = int ( cos( ( _RotationAngle + 0.0 ) * M_PI / 180.0 ) * _CurrentMovementSpeed );
		_VelocityY = int ( sin( ( _RotationAngle + 0.0 ) * M_PI / 180.0 ) * _CurrentMovementSpeed );

	}

	if( noCollision == true )
	{
		_Container->x += _VelocityX;
		_Container->y += _VelocityY;

		//update collision block		
		_pCollisionBox->x += _VelocityX;
		_pCollisionBox->y += _VelocityY;
	}
	else
	{
		_Container->x -= _VelocityX;
		_Container->y -= _VelocityY;

		//update collision block
		_pCollisionBox->x -= _VelocityX;
		_pCollisionBox->y -= _VelocityY;
	}

	//update sector location
	GameObjectHolder::instance().HandleSectorMovement( this );
}

void GameObject::UpdateWalkSprite( bool noCollision )
{
	bool update = true;

	if( Initialize::CurrentMovementType == Initialize::CompasMovement && noCollision == true )
	{
		//yupdate (based on direction)
		if( _VelocityX == 0 && _VelocityY == 0 )
		{
			update = false;
		}
	  
		if( _RotationAngle == 0 )
		{
			_CurrentSpritePossitionY = Initialize::SpriteRightMotion;
		}

		else if( _RotationAngle == 180 )
		{
			_CurrentSpritePossitionY = Initialize::SpriteLeftMotion;
		}

		else if( _RotationAngle == 90 )
		{
			_CurrentSpritePossitionY = Initialize::SpriteDownMotion;
		}

		else if( _RotationAngle == 270 )
		{
			_CurrentSpritePossitionY = Initialize::SpriteUpMotion;
		}

		if( !update ) 
		{
			_CurrentSpritePossitionX = 0;
		}

		for( vector< vector<Point> >::iterator i = _SpriteMap->begin(); i < _SpriteMap->end(); i++ )
		{
			bool set = false;

			int pos = abs( ( _SpriteMap->begin() - i ) );

			if( pos == _CurrentSpritePossitionY )
			{
				vector<Point> pointvect = ( *i );

				for( vector<Point>::iterator z = pointvect.begin(); z < pointvect.end(); z++ )
				{
					Point point = ( *z );

					if( abs( ( pointvect.begin() - z ) ) == _CurrentSpritePossitionX )
					{
						_pSpriteClip->x = point.X;
						_pSpriteClip->y = point.Y;
						_pSpriteClip->w = point.Width;
						_pSpriteClip->h = point.Height;

						set = true;

						//set or reset x (rotate round vector)
						_CurrentSpritePossitionX++;

						int size = pointvect.size(); 

						if( _CurrentSpritePossitionX >= size )
						{
							_CurrentSpritePossitionX = 0;
						}

						break;
					}
				}

				if( set )
				{
					break;
				}
			}
		}
	}
}

void GameObject::ResetSpriteX()
{
	_pSpriteClip->x = 0;
}

void GameObject::UpdateVelocity( int xVelIncrease, int yVelIncrease )
{
	_VelocityX += xVelIncrease;
	_VelocityY += yVelIncrease;
}

void GameObject::SetVelocity( int xVel, int yVel )
{
	_VelocityX = xVel;
	_VelocityY = yVel;
}

void GameObject::SetMovable( bool movable )
{
	_Movable = movable;
}

bool GameObject::GetMovable()
{
	return _Movable;
}

int GameObject::GetXVelocity()
{
	return _VelocityX;
}

int GameObject::GetYVeloctiy()
{
	return _VelocityY;
}

void GameObject::UpadetCamora( Camora* camora, SDL_Rect* levelBoudories )
{
	//centre camora over dot
	int x = 0, y = 0;

	x = int ( ( _Container->x + ( _Container->w / 2.0 ) ) - ( camora->GetRect()->w / 2.0 ) );
	y = int ( ( _Container->y + ( _Container->h / 2.0 ) ) - ( camora->GetRect()->h / 2.0 ) );

	//Keep the camera in bounds.
    if( x < 0 )
    {
        x = 0;    
    }

    if( y < 0 )
    {
        y = 0;    
    }

	if( x + camora->GetRect()->w  > levelBoudories->w )
    {
        x = levelBoudories->w - camora->GetRect()->w;   
    }

    if( y + camora->GetRect()->h > levelBoudories->h )
    {
        y = levelBoudories->h - camora->GetRect()->h;
	}

	camora->Update( x, y );

}

bool GameObject::GetIsAnimating()
{
	return _IsAnimating;
}

void GameObject::SwordAttackAnimation()
{
	_CurrentAnimation = Initialize::AnimationSwordAttack;
	_IsAnimating = true;
	_AnimationRate = Initialize::AttackAnimationRate;
}

void GameObject::BowArrowAnimation()
{
	_CurrentAnimation = Initialize::AnimationBowArrow;
	_IsAnimating = true;
	_AnimationRate = Initialize::AttackAnimationRate;
}

void GameObject::UpdateSwordSprite()
{
	bool update = false;

	if( Initialize::CurrentMovementType == Initialize::CompasMovement )
	{
		//yupdate (based on direction)
		if( _RotationAngle == 0 )
		{
			_CurrentSpritePossitionY = Initialize::SpriteSwordRight;
			update = true;
		}

		else if( _RotationAngle == 180 )
		{
			_CurrentSpritePossitionY = Initialize::SpriteSwordLeft;
			update = true;
		}

		else if( _RotationAngle == 90 )
		{
			_CurrentSpritePossitionY = Initialize::SpriteSwordDown;
			update = true;
		}

		else if( _RotationAngle == 270 )
		{
			_CurrentSpritePossitionY = Initialize::SpriteSwordUp;
			update = true;
		}

 		if( update == true )
		{
			for( vector< vector<Point> >::iterator i = _SpriteMap->begin(); i < _SpriteMap->end(); i++ )
			{
				bool set = false;

				int pos = abs( ( _SpriteMap->begin() - i ) );

				if( pos == _CurrentSpritePossitionY )
				{
					vector<Point> pointvect = ( *i );

					for( vector<Point>::iterator z = pointvect.begin(); z < pointvect.end(); z++ )
					{
						Point point = ( *z );

						if( abs( ( pointvect.begin() - z ) ) == _CurrentSpritePossitionX )
						{
							_pSpriteClip->x = point.X;
							_pSpriteClip->y = point.Y;
							_pSpriteClip->w = point.Width;
							_pSpriteClip->h = point.Height;

							set = true;

							//set or reset x (rotate round vector)
							_CurrentSpritePossitionX++;

							int size = pointvect.size(); 

							if( _CurrentSpritePossitionX >= size )
							{
								//end of animation
								_CurrentSpritePossitionX = 0;
				
								//stop animating, set animation back to walk
								_IsAnimating = false;
								_CurrentAnimation = Initialize::AnimationRun;
								_AnimationRate = Initialize::RunAnimationRate;	
							}

							break;
						}
					}

					if( set )
					{
						break;
					}
				}
			}
		}
	}
}

void GameObject::UpdateBowArrowSprite()
{
	bool update = false;

	if( Initialize::CurrentMovementType == Initialize::CompasMovement )
	{
		//yupdate (based on direction)
		if( _RotationAngle == 0 )
		{
			_CurrentSpritePossitionY = Initialize::SpriteBowArrowRight;
			update = true;
		}

		else if( _RotationAngle == 180 )
		{
			_CurrentSpritePossitionY = Initialize::SpriteBowArrowLeft;
			update = true;
		}

		else if( _RotationAngle == 90 )
		{
			_CurrentSpritePossitionY = Initialize::SpriteBowArrowDown;
			update = true;
		}

		else if( _RotationAngle == 270 )
		{
			_CurrentSpritePossitionY = Initialize::SpriteBowArrowUp;
			update = true;
		}

		if( update == true )
		{
			for( vector< vector<Point> >::iterator i = _SpriteMap->begin(); i < _SpriteMap->end(); i++ )
			{
				bool set = false;

				int pos = abs( ( _SpriteMap->begin() - i ) );

				if( pos == _CurrentSpritePossitionY )
				{
					vector<Point> pointvect = ( *i );

					for( vector<Point>::iterator z = pointvect.begin(); z < pointvect.end(); z++ )
					{
						Point point = ( *z );

						if( abs( ( pointvect.begin() - z ) ) == _CurrentSpritePossitionX )
						{
							_pSpriteClip->x = point.X;
							_pSpriteClip->y = point.Y;
							_pSpriteClip->w = point.Width;
							_pSpriteClip->h = point.Height;

							set = true;

							//set or reset x (rotate round vector)
							_CurrentSpritePossitionX++;

							int size = pointvect.size(); 

							if( _CurrentSpritePossitionX >= size )
							{
								//end of animation
								_CurrentSpritePossitionX = 0;
				
								//stop animating, set animation back to walk
								_IsAnimating = false;
								_CurrentAnimation = Initialize::AnimationRun;
								_AnimationRate = Initialize::RunAnimationRate;	
							}

							break;
						}
					}

					if( set )
					{
						break;
					}
				}
			}
		}
	}
}

int GameObject::GetDirection()
{
	return _RotationAngle;
}

void GameObject::SetMoveDirection( int moveNumber )
{
	_MoveDirection = moveNumber;

	if( moveNumber == GameObject::MOVESTOP )
	{
		_VelocityX = 0;
		_VelocityY = 0;
	}
	else if( moveNumber == GameObject::MOVENORTH )
	{
		_VelocityX = 0;
		_VelocityY = 0 - _MovementSpeed;
		_RotationAngle = 270;
	}
	else if( moveNumber == GameObject::MOVENORTHEAST )
	{
		_VelocityX = _MovementSpeed;
		_VelocityY = 0 - _MovementSpeed;
	}
	else if( moveNumber == GameObject::MOVEEAST )
	{
		_VelocityX = _MovementSpeed;
		_VelocityY = 0;
		_RotationAngle = 0;
	}
	else if( moveNumber == GameObject::MOVESOUTHEAST )
	{
		_VelocityX = _MovementSpeed;
		_VelocityY = _MovementSpeed;
	}
	else if( moveNumber == GameObject::MOVESOUTH )
	{
		_VelocityX = 0;
		_VelocityY = _MovementSpeed;
		_RotationAngle = 90;
	}
	else if( moveNumber == GameObject::MOVESOUTHWEST )
	{
		_VelocityX = 0 -_MovementSpeed;
		_VelocityY = _MovementSpeed;
	}
	else if( moveNumber == GameObject::MOVEWEST )
	{
		_VelocityX = 0 -_MovementSpeed;
		_VelocityY = 0;
		_RotationAngle = 180;
	}
	else if( moveNumber == GameObject::MOVENORTHWEST )
	{
		_VelocityX = 0 -_MovementSpeed;
		_VelocityY = 0 - _MovementSpeed;
	}
}

int GameObject::GetMoveDirection()
{
	return _MoveDirection;
}

bool GameObject::GetIsIntelligent() const
{
	return _IsIntelligent;
}

int GameObject::GetObjectType()
{
	return _ObjectType;
}

bool GameObject::GetIsInteractable()
{
	return _IsInteractable;
}

int GameObject::GetEntityType()
{
	return _EntityType;
}