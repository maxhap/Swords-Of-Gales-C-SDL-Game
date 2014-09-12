#include "stdafx.h"

using namespace std;

LogicEngine::LogicEngine()
{
	//just to initlaise changed in main loop
	_CurrentGameState = 0;

	_Quit = false;

	_pGameTimer = new GameTimer();
	_pMainWnd = new MainWnd();
	_pMainWnd->SetRenderMode( MainWnd::SDL_RENDER );

	_pCamora = new Camora( 0, 0, Initialize::BattleGroundWidth, Initialize::BattleGroundHeight );

	//systems
	_pInventorySystem = NULL;
	_RupeeDisplay = new RupeeDisplay( Initialize::RupeeDisplayX, Initialize::RupeeDisplayY, Initialize::RupeeDisplayWidth, Initialize::RupeeDisplayHeight, Initialize::RupeeDisplayImageLocation );	
	_ArrowDisplay = new ArrowDisplay( Initialize::ArrowDisplayX, Initialize::ArrowDisplayY, Initialize::ArrowDisplayWidth, Initialize::ArrowDisplayHeight, Initialize::ArrowDisplayImageLocation );	

	_StateTracker = 0;

	tmpList = new vector<GameObject*>;
}

LogicEngine::~LogicEngine()
{
	delete _pGameTimer;
	delete _pCamora;
	delete _pInventorySystem;
	delete _pCharacterDisplaySystem;

	MemoryManagement<GameObject>::instance().CleanVector( tmpList, false );
}

bool LogicEngine::Initialize()
{
	//systems
	_pInventorySystem = new InventorySystem( Initialize::InventorySystemXPosition, Initialize::InventorySystemYPosition, Initialize::InventorySystemWidth, Initialize::InventorySystemHeight, Initialize::InventorySystemBackgroundLocation, Initialize::InventorySystemActiveBackgroundLocation	 ,Initialize::InventorySystemCopacity, Initialize::InventoryItemWidth, Initialize::InventoryItemHeight );
	
	_pCharacterDisplaySystem = new CharacterDisplaySystem( Initialize::DisplaySystemXPosition, Initialize::DisplaySystemYPosition, Initialize::DisplaySystemWidth, Initialize::DisplaySystemHeight, Initialize::DisplaySystemBackgroundLocation );

	CombatSystem::instance().AddInventorySystem( _pInventorySystem );

	//init of systems
	if( _pMainWnd->Init() == false )
	{
		ErrorSystem::instance().WriteError( "Logic Engine init fail" );
		return false;
	}
	
	if( LevelSystem::instance().LoadWelcomeScreen( Initialize::StartScreenFileLocatin ) == false )
	{
		ErrorSystem::instance().WriteError( "Logic Engine startlevel fail" );
		return false;
	}

	if( _pCharacterDisplaySystem->LoadDisplayImage() == false )
	{
		ErrorSystem::instance().WriteError( "Logic Engine load display fail" );
		return false;
	}

	if( _RupeeDisplay->LoadDisplayImage() == false )
	{
		ErrorSystem::instance().WriteError( "Logic Engine rupee display load fail" );
		return false;
	}

	if( _ArrowDisplay->LoadDisplayImage() == false )
	{
		ErrorSystem::instance().WriteError( "Logic Engine Arrow display load fail" );
		return false;
	}

	//player setup
	Player* player = GameObjectFactory::instance().GetPlayer();
	
	if( player == NULL )
	{
		return false;
	}
	else
	{
		GameObjectHolder::instance().AddPlayer( player );
		_pInventorySystem->AddPlayer( player );
		_pCharacterDisplaySystem->AddPlayer( player );
	}

	if( GameObjectHolder::instance().GetPlayer()->LoadItemImage() == false )
	{
		ErrorSystem::instance().WriteError( "Logic Engine load player image fail" );
		return false;
	}

	if( _pInventorySystem->LoadInventoryImage() == false )
	{
		ErrorSystem::instance().WriteError( "Logic Engine load inventory image fail" );
		return false;
	}

	if( GameObjectHolder::instance().LoadAllObjectSprites() == false )
	{
		ErrorSystem::instance().WriteError( "Logic Engine fail to load object sprites" );
		return false;
	}	

	return true;
}

bool LogicEngine::Quit()
{
	TileObjectHolder::instance().DestroySectors();


	if( _pMainWnd->CleanUp() == false )
	{
		ErrorSystem::instance().WriteError( "Logic Engine clean up fail" );
		return false;
	}

	return true;
}

bool LogicEngine::CollisionCheck( GameObject* object )
{
	bool collision = false;

	//collision detection level area
	if( object->HasColided( NULL ) == false )
	{
		collision = true;
	}

	if( collision != true )
	{
		//collision against tiles
		vector<GameSector*>* tilCollisionList = TileObjectHolder::instance().GetSectorsContaining( object->Container() );
		
		for( vector<GameSector*>::iterator i = tilCollisionList->begin(); i < tilCollisionList->end(); i++ )
		{
			vector<GameObject*>* objectList = ( *i )->GetAll();

			if( collision != true )
			{
				for( vector<GameObject*>::iterator z = objectList->begin(); z < objectList->end(); z++ )
				{
					Tile* tile = ( Tile* ) ( *z );

					if( tile->GetType() == Initialize::TileTypePlain )
					{
						//do nothing so far
					}
					else if( tile->GetType() == Initialize::TileTypleWall )
					{
						//detect colission
						if( GameObjectHolder::instance().GetPlayer()->HasColided( tile ) == true )
						{
							collision = true;
							break;
						}
					}
				}
			}
			else 
			{
				break;
			}
		}

		MemoryManagement<GameSector>::instance().CleanVector( tilCollisionList, false );
	}

	if( collision != true )
	{
		//collision other game obejects
		vector<GameSector*>* objectCollisionList = GameObjectHolder::instance().GetSectorsContaining( object->Container() );
		
		for( vector<GameSector*>::iterator i = objectCollisionList->begin(); i < objectCollisionList->end(); i++ )
		{
			if( collision != true )
			{
				vector<GameObject*>* objectList = ( *i )->GetAll();
				
				for( vector<GameObject*>::iterator z = objectList->begin(); z < objectList->end(); z++ )
				{
					if( object != ( *z ) && ( *z )->HasColided( object ) == true )
					{
						collision = true;
						break;
					}
				}
			}
			else
			{
				break;
			}
		}

		MemoryManagement<GameSector>::instance().CleanVector( objectCollisionList, false );
	}

	return collision;
}

bool LogicEngine::ItemCollisionCheck( Character* character )
{
	bool collision = false;

	vector<Item*>* items = GameObjectHolder::instance().GetGameItemContainer();

	Item* colidedItem = NULL;
	
	for( vector<Item*>::iterator i = items->begin(); i < items->end(); i++ )
	{
		if( ( *i )->HasColided( character ) )
		{
			collision = true;
			colidedItem = ( *i );
			break;
		}
	}

	if( colidedItem != NULL )
	{
		GameObjectHolder::instance().RemoveFromItemContainer( colidedItem );

		if( colidedItem->Aquire() )
		{
			InventoryItem* madeItem = colidedItem->ConvertToInventoryItem();

			GameObjectHolder::instance().GetPlayer()->AddItem( madeItem );
		}

		delete ( colidedItem );
	}

	return collision;
}

void LogicEngine::LevelSwitch()
{
	if( _CurrentGameState == GameState::LEVELSWITCH )
	{
		//load level

		LevelSystem::instance().DestroyCurrentLevel();

		string nextLevelFile = LevelSystem::instance().GetNextLevelFileLocation();
		string nextEntryID = LevelSystem::instance().GetNextLevelEntryPointID();

		if( nextLevelFile.compare("") == 0 || nextEntryID.compare("") == 0 )
		{
			ErrorSystem::instance().WriteError( "Next Level comapre = " + nextLevelFile + " - Failed " );
			_Quit = true;
		}

		if( LevelSystem::instance().LoadLevel( nextLevelFile ) == false )
		{
			ErrorSystem::instance().WriteError( "Level Failed To load" );
			_Quit = true;
		}

		if( GameObjectHolder::instance().LoadAllObjectSprites() == false )
		{
			ErrorSystem::instance().WriteError( "Object Sprite Failed To Load" );
			_Quit = true;
		}	

		_CurrentGameState = GameState::LEVELLOADWAIT;
		_StateTracker = 0;

		//setplayer
		Character* player = GameObjectHolder::instance().GetPlayer();

		player->SetVelocity( 0, 0 );

		//find beakon
		Beacon* beacon = GameObjectHolder::instance().FindBeacon( nextEntryID );

		if( beacon != NULL )
		{
			player->SetAbsolutePosition( beacon->GetEntryLocation()->X, beacon->GetEntryLocation()->Y );
		}
		else
		{
			//set default quanardiantes
		}
	}
	else if ( _CurrentGameState == GameState::LEVELLOADWAIT )
	{
		if( _StateTracker < 50 )
		{
			_StateTracker++;
			_pMainWnd->ClearScreen();
		}
		else
		{
			_CurrentGameState = GameState::GAMEPLAYEXPLOREMODE;
			_StateTracker = 0;
		}
	}

}

bool LogicEngine::GameLoop()
{
	int runTime = 0;
	
	//Timer used to update the caption
    GameTimer update;
	//Start the update timer
    update.Start();

	while( _Quit == false )
	{
		DetermineGameState();
		_CurrentGameState = GameState::instance().GetGameState();

		int frame = 0;
		
		//reset game timer
		_pGameTimer->Start();
		/*-------------------------------------------------------------------- START OF Events ----------------------------------------------------------*/
			
		HandleEvents();
		/*-------------------------------------------------------------------- End OF Events----------------------------------------------------------*/

		/*-------------------------------------------------------------------- START OF LOGIC ----------------------------------------------------------*/
		if( _CurrentGameState == GameState::WELCOMEDISPLAY )
		{
			DrawStartScreen();
		}
		if( _CurrentGameState == GameState::GAMEPLAYEXPLOREMODE || _CurrentGameState == GameState::GAMEPLAYSHOPMODE )
		{
			UpdateObjects();

			PlayerCollisionDetection();

			Draw();				
		}

		/*------------------------- Start OF Drawing ------------------------------------*/


		/*------------------------- End OF Drawing ------------------------------------*/


		LevelSwitch();


		/*------------------------------------------------------------------ END OF LOGIC -------------------------------------------------------*/

		//Update the screen
		if( SDL_Flip( _pMainWnd->GetSurface() ) == -1 )
		{
			return false;    
		}

		
		//cap frame rate
		if( _pGameTimer->GetTicks() < 1000 / Initialize::FRAMERATE  )
		{
			SDL_Delay( ( 1000 / Initialize::FRAMERATE  ) - _pGameTimer->GetTicks() );
		}		

		//Increment the frame counter
        frame++;

		 //If a second has passed since the caption was last updated
		if( update.GetTicks() > 1000 )
        {
            //The frame rate as a string
            std::stringstream caption;

            //Calculate the frames per second and create the string 
            caption << "Average Frames Per Second: " << frame / ( _pGameTimer->GetTicks()/ 1000.f ) << "    Runtime: " << runTime;

            //Reset the caption
            SDL_WM_SetCaption( caption.str().c_str(), NULL );

            //Restart the update timer
            update.Start();
			runTime++;
        }
	}

	return true;
}

void LogicEngine::HandleEvents()
{
	if( SDL_PollEvent( &event ) )
	{
		if( event.type == SDL_QUIT )
		{
			_Quit = true;
		}

		if( event.type == SDL_KEYDOWN || event.type == SDL_KEYUP )
		{
			//pop event from sdl key stack
			SDLKey key = event.key.keysym.sym;

			/*--Game State Dependant--*/
			//start screen
			if( _CurrentGameState == GameState::WELCOMEDISPLAY )
			{
				if( key == SDLK_RETURN )
				{
					LevelSystem::instance().SetLevelToSwitch( true );
				}
			}

			//Explorer mode
			else if( _CurrentGameState == GameState::GAMEPLAYEXPLOREMODE )
			{
				//movment keys
				if( key == SDLK_UP || key == SDLK_DOWN || key == SDLK_RIGHT || key == SDLK_LEFT )
				{
					GameObjectHolder::instance().GetPlayer()->HandleInput( event );
				}

				//inventory keys
				if( key == SDLK_0 || key == SDLK_1 || key == SDLK_2 || key == SDLK_3 || key == SDLK_4 || key == SDLK_5 || key == SDLK_6 ||key == SDLK_7 || key == SDLK_8 || key == SDLK_9 )
				{
					_pInventorySystem->HandleInput( event );
				}			

				//combat keys
				if( key == SDLK_SPACE )
				{
					Player* player = GameObjectHolder::instance().GetPlayer(); 

					if( event.type == SDL_KEYUP && player ->GetSomethingToIntercatWith() )
					{
						player ->InitiateInteraction();
					}
					else
					{
						if( player ->GetIsAnimating() == false )
						{
							CombatSystem::instance().HandleEvent( event );
						}
					}
				}	

				//debug keys
				if( key == SDLK_p )
				{
					int x = GameObjectHolder::instance().GetPlayer()->Container()->x;
					int y = GameObjectHolder::instance().GetPlayer()->Container()->y;

					cout << "x = " << x << "\n" << "y = " << y << "\n";
				}
			}

			//shop mode
			else if( _CurrentGameState == GameState::GAMEPLAYSHOPMODE )
			{
				if( key == SDLK_ESCAPE )
				{
					LevelSystem::instance().SetShopToDisplay( false );
				}
				else
				{
					LevelSystem::instance().GetCurrentLevel()->GetShop()->HandleInput( event );
				}
			}


		}	
	}
}

void LogicEngine::UpdateObjects()
{
		//update objects
		GameObjectHolder::instance().GetPlayer()->Update( true );

		vector<GameObject*>* gameObjectList = GameObjectHolder::instance().GetGameEntityContainer();

		for( vector<GameObject*>::iterator i = gameObjectList->begin(); i < gameObjectList->end(); i++ )
		{
			//check for interaction
			if( ( *i )->GetIsInteractable() )
			{
				InteractableGameObject* igo = ( InteractableGameObject* ) ( *i );
				igo->WithinInteractionRange( GameObjectHolder::instance().GetPlayer() );
			}

			if( ( *i )->GetObjectType() == Initialize::SpikeTrap )
			{
				( *i )->Update( true );
			}

			if( ( *i )->GetMovable() )
			{
				bool collision = false;

				if( ( *i )->Update( true ) == false ) 
				{
					MemoryManagement<GameObject>::instance().AddToDumpList( *i );
					ItemHandler::instance().AddRandomItem( 1, ( *i )->Container()->x, ( *i )->Container()->y );
					collision = true;
				}
				else
				{
					//object collision detection
					if( CollisionCheck( *i ) )
					{
						( *i )->Update( false );
					}
					else if( GameObjectHolder::instance().GetPlayer()->HasColided( NULL ) == false )
					{
						( *i )->Update( false );
					}
				}

				if( !collision )
				{
					( *i )->Update( true, true );
				}
			}
		}

		MemoryManagement<GameObject>::instance().RemoveDumpListFromGamePlay();
		MemoryManagement<GameObject>::instance().FlushDumpList();

		//update systems
		CombatSystem::instance().Update();
}

void LogicEngine::PlayerCollisionDetection()
{
	//collision detection for player
	if( CollisionCheck( GameObjectHolder::instance().GetPlayer() ) )
	{
		GameObjectHolder::instance().GetPlayer()->Update( false );
	}

	if( GameObjectHolder::instance().GetPlayer()->HasColided( NULL ) == false )
	{
		GameObjectHolder::instance().GetPlayer()->Update( false );
	}

	ItemCollisionCheck( GameObjectHolder::instance().GetPlayer() );
}

void LogicEngine::Draw()
{
	//draw list( clean up at end )	
	vector<GameObject*>* drawList = new vector<GameObject*>;

	if( _CurrentGameState == GameState::GAMEPLAYEXPLOREMODE || _CurrentGameState == GameState::GAMEPLAYSHOPMODE )
	{
		_pMainWnd->ClearScreen();
		GameObjectHolder::instance().GetPlayer()->UpadetCamora( _pCamora, LevelSystem::instance().GetCurrentLevel()->GetContainer() );

		//draw level and objects
		LevelSystem::instance().GetCurrentLevel()->PaintBackground( _pMainWnd, _pCamora->GetRect() );

		//projectiles from combat system
		CombatSystem::instance().DrawProjectiles( _pMainWnd, _pCamora );

		/*---------------------------Test Mode----------------------------*/
		//only draw in test mode
		if( Initialize::TestMode == true )
		{
			//drawing of tiles 
			vector<GameSector*>* tileDrawList = TileObjectHolder::instance().GetSectorsContaining( _pCamora->GetRect() );

			for( vector<GameSector*>::iterator i = tileDrawList->begin(); i < tileDrawList->end(); i++ )
			{
				vector<GameObject*>* objectList = ( *i )->GetAll();
			
				for( vector<GameObject*>::iterator z = objectList->begin(); z < objectList->end(); z++ )
				{
					( *z )->Draw( _pMainWnd, _pCamora );
				}
			}

			MemoryManagement<GameSector>::instance().CleanVector( tileDrawList, false );

			//player test rect
			GameObjectHolder::instance().GetPlayer()->DrawTestRect( _pMainWnd, _pCamora );

			//game objects test rect
			vector<GameSector*>* drawList = GameObjectHolder::instance().GetSectorsContaining( _pCamora->GetRect() );

			for( vector<GameSector*>::iterator i = drawList->begin(); i < drawList->end(); i++ )
			{
				vector<GameObject*>* objectList = ( *i )->GetAll();
			
				for( vector<GameObject*>::iterator z = objectList->begin(); z < objectList->end(); z++ )
				{
					( *z )->DrawTestRect( _pMainWnd, _pCamora );
				}
			}		
		}

		CombatSystem::instance().DrawTestAreas( _pMainWnd, _pCamora );

		/*---------------------------End Test Mode----------------------------*/

		//draw game objects
		vector<GameSector*>* sectorList = GameObjectHolder::instance().GetSectorsContaining( _pCamora->GetRect() );
		
		for( vector<GameSector*>::iterator i = sectorList->begin(); i < sectorList->end(); i++ )
		{
			vector<GameObject*>* objectList = ( *i )->GetBlockers();
			vector<GameObject*>* objectListEntities = ( *i )->GetEntities();

			//combine into one list (all objects equal at draw time)
			vector<GameObject*>* allObjectsInSector = new vector<GameObject*>;
			allObjectsInSector->insert( allObjectsInSector->end(), objectList->begin(), objectList->end() );
			allObjectsInSector->insert( allObjectsInSector->end(), objectListEntities->begin(), objectListEntities->end() );

			for( vector<GameObject*>::iterator i = allObjectsInSector->begin(); i < allObjectsInSector->end(); i++ )
			{	
				
				vector<GameObject*>* miniDrawList = new vector<GameObject*>;

				//create
				if( ( *i )->GetDrawMark() == Object::NOMARK )
				{
					miniDrawList->insert( miniDrawList->end(), 1, ( *i ) );
					( *i )->SetDrawMark( Object::DRAWMARK );

					if( allObjectsInSector->size() > 1 )
					{
						BuildCollisionList( ( *i ), allObjectsInSector, miniDrawList );
						//sort mini draw list
 						SortList( miniDrawList );
					}
				}

				//mark all minilist items
				for( vector<GameObject*>::iterator x = miniDrawList->begin(); x < miniDrawList->end(); x++ )
				{
					( *x )->SetDrawMark( Object::DRAWMARK );
				}

				//add minidraw list to draw list
				drawList->insert( drawList->end(), miniDrawList->begin(), miniDrawList->end() );

				MemoryManagement<GameObject>::instance().CleanVector( miniDrawList, false );

			}			

			MemoryManagement<GameObject>::instance().CleanVector( allObjectsInSector, false );
			
		}
		MemoryManagement<GameSector>::instance().CleanVector( sectorList, false );
		
		//draw game items
		vector<Item*>* itemDrawList = GameObjectHolder::instance().GetGameItemContainer();

		for( vector<Item*>::iterator i = itemDrawList->begin(); i < itemDrawList->end(); i++ )
		{
			( *i )->Draw(  _pMainWnd, _pCamora  );
			( *i )->SetDrawMark( Object::NOMARK );
		}					
	}	

	//draw object in draw drawlist
	for( vector<GameObject*>::iterator z = drawList->begin(); z < drawList->end(); z++ )
	{
		( *z )->Draw( _pMainWnd, _pCamora );
		( *z )->SetDrawMark( Object::NOMARK );
	}

	//draw shop if mode
	if( _CurrentGameState == GameState::GAMEPLAYSHOPMODE )
	{
		LevelSystem::instance().GetCurrentLevel()->GetShop()->Draw( _pMainWnd, _pCamora );
	}	

	//draw rupys & arrows
	_RupeeDisplay->DrawDisplay( _pMainWnd );
	_ArrowDisplay->DrawDisplay( _pMainWnd );
		

	//draw items
	_pInventorySystem->DrawInventoryItems( _pMainWnd );

	//draw hear display system
	_pCharacterDisplaySystem->DrawCharacterHealth( _pMainWnd );

	MemoryManagement<GameObject>::instance().CleanVector( drawList, false );
}

void LogicEngine::DrawStartScreen()
{
	_pCamora->Update( 0, 0 );
	LevelSystem::instance().GetCurrentLevel()->PaintBackground( _pMainWnd, _pCamora->GetRect() );
}

void LogicEngine::DetermineGameState()
{
	
	//check for new level
	if( LevelSystem::instance().GetLevelToSwitch() )
	{
		LevelSystem::instance().SetLevelToSwitch( false );
		GameState::instance().SetGameState( GameState::LEVELSWITCH );
	}
	else if( GameState::instance().GetGameState() == GameState::WELCOMEDISPLAY )
	{
		//do nothing as handle event changes this
	}
	//check to display shop
	else if( LevelSystem::instance().GetShopToDisplay() )
	{
		GameState::instance().SetGameState( GameState::GAMEPLAYSHOPMODE );
	}
	
	else
	{
		GameState::instance().SetGameState( GameState::GAMEPLAYEXPLOREMODE );
	}

}

void LogicEngine::BuildCollisionList( GameObject* object, vector<GameObject*>* allObjectsInSector, vector<GameObject*>* collisionList )
{
	//list to tmp hold colided objects	

	//build collision list
	for( vector<GameObject*>::iterator i = allObjectsInSector->begin(); i < allObjectsInSector->end(); i++ )
	{
		//if objects are not the same insert into mark and insert into collision list
		if( ( *i ) != object  )
		{			
			bool collision = object->HasColidedRect( ( *i )->Container() );

			if( collision )
			{											
				if( ( *i )->GetDrawMark() == Object::NOMARK )
				{
					( *i )->SetDrawMark( Object::COLIDEDMARK );
					InsertIntoList( ( *i ), collisionList, -1 );
					BuildCollisionList( ( *i ), allObjectsInSector, collisionList );
				}
			}
		}
	}	
}

void LogicEngine::InsertIntoList( GameObject* object, vector<GameObject*>* list, int possition )
{
	if( object->GetDrawMark() != Object::DRAWMARK )
	{
		if( possition == -1 )
		{
			list->insert( list->end(), 1, object );
		}
		else if( possition == -2 )
		{
			list->insert( list->begin(), 1, object );
		}
		else
		{
			list->insert( list->begin() + possition, 1, object );
		}		
	}
}

void LogicEngine::SortList( vector<GameObject*>* listToSort )
{	
	//decide on sorting accuracy	
	int cycle = 1;

	if( listToSort->size() > 3 )
	{
		//cycle = 2;
	}

	for( int c = 0; c < cycle; c++ )
	{
		//implement sort

		for( vector<GameObject*>::iterator i = listToSort->begin(); i < listToSort->end(); i++ )
		{		
			vector<GameObject*>::iterator possition = tmpList->end();

			if( ( *i )->GetAlwaysDrawBefore() )
			{
				possition = tmpList->begin();
			}
			else if( tmpList->size() != 0 )
			{
				for( vector<GameObject*>::iterator z = tmpList->begin(); z < tmpList->end(); z++ )
				{
					if( ( *i )->CheckIsAbove( ( *z )->Container() ) )
					{
						//move to possition below
						if( z != tmpList->begin() )
						{
							possition = z-1;
						}
						else
						{
							possition = tmpList->begin();
						}
						break;
					}
					else
					{
						if( z != tmpList->end() )
						{
							possition = z+1;
						}
						else
						{
							possition = tmpList->end();	
						}
					}
				}
			}
		
			tmpList->insert( possition, 1, ( *i ) );
		}

		//swap then empty lists
		listToSort->erase( listToSort->begin(), listToSort->end() );
		listToSort->insert( listToSort->end(), tmpList->begin(), tmpList->end() );
		tmpList->erase( tmpList->begin(), tmpList->end() ); 
	}
}