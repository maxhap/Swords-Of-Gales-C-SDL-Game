#include "stdafx.h"

using namespace std;

Level::Level( string levelfile )
{
	_LevelFile = levelfile;
	_ShopLevel = false;

	_pContainer = new SDL_Rect();
	_pTileDimentions = new SDL_Rect();

	_pBackground = NULL;
	_pShop = NULL;
}

Level::~Level()
{
	delete _pBackground;
	delete _pContainer;
	delete _pTileDimentions;
	
	if( _pShop != NULL )
	{
		delete _pShop;
	}
}

bool Level::LoadProperties()
{
	/*--------------------------- Put Errors in Read ----------------------------*/
	ifstream file ( _LevelFile );

	if( file.is_open() )
	{
		string line;
		int lineReferance = 0; 
		bool propsFound = false;

		 while( file.good() )
		 {
			 getline( file, line );	
			  
			 if( !propsFound && line.compare( "--Properties--" ) == 0 )
			 {
				 propsFound = true;
			 }

			 if( propsFound )
			 {
				 if( line.compare( 0, 2, "id" ) == 0 )
				 {
					 _levelID = line.substr( 3 );
				 }
				 else if( line.compare( 0, 5, "width" ) == 0 )
				 {
					 _pContainer->w = StringConverter::StringToInt( line.substr( 6 ), "Error - LevelWidthRead" );
				 }
				 else if( line.compare( 0, 6, "height" ) == 0 )
				 {
					 _pContainer->h = StringConverter::StringToInt( line.substr( 7 ), "Error - LevelHeightRead" );
				 }
				 else if( line.compare( 0, 9, "tilewidth" ) == 0 )
				 {
					 _pTileDimentions->w = StringConverter::StringToInt( line.substr( 10 ), "Error - TileWidthRead" );
				 }
				 else if( line.compare( 0, 10, "tileheight" ) == 0 )
				 {
					 _pTileDimentions->h = StringConverter::StringToInt( line.substr( 11 ), "Error - TileHeighthRead" );
				 }
				 else if( line.compare( 0, 10, "totaltiles" ) == 0 )
				 {
					 _TotalTiles = StringConverter::StringToInt( line.substr( 11 ), "Error - TotalTilesRead" );
				 }
				 else if( line.compare( 0, 22, "backgroundfilelocation" ) == 0 )
				 {
					 _BackgroundFileLocation = line.substr( 23 );
				 }
				 else if( line.compare( 0, 21, "tiletestimagelocation" ) == 0 )
				 {
					 _TileTestImageLocation = line.substr( 22 );
				 }
				 else if( line.compare( 0, 26, "blocktiletestimagelocation" ) == 0 )
				 {
					 _BlockTileTestImageLocation = line.substr( 27 );
				 }
				 else if( line.compare( 0, 9, "shoplevel" ) == 0 )
				 {
					 if( line.compare( 10, line.size(), "true" ) == 0 )
					 {
						 _ShopLevel = true;
					 }					 
				 }
				 else if( line.compare( "--End--") == 0 )
				 {
					 break;
				 }
			 }		
		 }
	}

	file.close();

	return true;
}

bool Level::LoadShop()
{
	if( _ShopLevel )
	{
		bool itemsFound = false;
		/*--------------------------- Put Errors in Read ----------------------------*/
		ifstream file ( _LevelFile );

		if( file.is_open() )
		{
			string line;
			int lineReferance = 0;	

			 while( file.good() )
			 {				 
				 getline( file, line );

				 if( itemsFound == false && line.compare( "-ShopProperties-" ) == 0 )
				 {
					 int x =0;
					 int y = 0;
					 int width = 0;
					 int height = 0;
					 string backgroundImageLocation;

					 for( int i = 0; i < 5; i++ )
					 {
						 getline( file, line );

						 if( line.compare( 0, 4, "PosX" ) == 0 )
						 {
				 			 x = StringConverter::StringToInt( line.substr( 5 ), "xreadposx" );
						 }
						 else if( line.compare( 0, 4, "PosY" ) == 0 )
						 {
							 y = StringConverter::StringToInt( line.substr( 5 ), "xreadposy" );
						 }
						 else if( line.compare( 0, 5, "Width" ) == 0 )
						 {
							 width = StringConverter::StringToInt( line.substr( 6 ), "xreadwdth" );
						 }
						 else if( line.compare( 0, 6, "Height" ) == 0 )
						 {
							 height = StringConverter::StringToInt( line.substr( 7 ), "xreadheigh" );
						 }
						 else if( line.compare( 0, 23, "BackgroundImageLocation" ) == 0 )
						 {
							 backgroundImageLocation = line.substr( 24 );
						 }
					 }

					 _pShop = GameObjectFactory::instance().GetShop( x, y , width, height, backgroundImageLocation );

					 if( _pShop->LoadItemImage() == false )
					 {
						 ErrorSystem::instance().WriteError( "Failed to load shop background image" );

						 return false;
					 }
				 }

				 else if( line.compare( "-ShopItems-" ) == 0 )
				 {
					 itemsFound = true;
				 }

				 if( itemsFound )
				 {
					if( line.compare( "------------------------------------" ) == 0 )
					{
						getline( file, line );

						if( line.compare( 0, 4, "Item" ) == 0 )
						{
							if( line.compare( 5, line.size() - 5, "ArrowShopItem" ) == 0 )
							{
								int x = 0;
								int y = 0;
								int width = 0;
								int height = 0;
								int price = 0;
								int restoreAmount = 0;
								string backgroundImage = "";								

								for( int i = 0; i < 7; i++ )
								{
									getline( file, line );

									if( line.compare( 0, 4, "PosX" ) == 0 )
									{
										x = StringConverter::StringToInt( line.substr( 5 ), "xreadposx" );
									}
									else if( line.compare( 0, 4, "PosY" ) == 0 )
									{
										y = StringConverter::StringToInt( line.substr( 5 ), "xreadposy" );
									}
									else if( line.compare( 0, 5, "Width" ) == 0 )
									{
										width = StringConverter::StringToInt( line.substr( 6 ), "xreadwdth" );
									}
									else if( line.compare( 0, 6, "Height" ) == 0 )
									{
										height = StringConverter::StringToInt( line.substr( 7 ), "xreadheigh" );
									}
									else if( line.compare( 0, 5, "Price" ) == 0 )
									{
										price = StringConverter::StringToInt( line.substr( 6 ), "xreadprice" );
									}
									else if( line.compare( 0, 13, "RestoreAmount" ) == 0 )
									{
										restoreAmount = StringConverter::StringToInt( line.substr( 14 ), "xreadrestoreamount" );
									}
									else if( line.compare( 0, 15, "BackgroundImage" ) == 0 )
									{
										backgroundImage = line.substr( 16 );
									}
								}

								ArrowShopItem* item = GameObjectFactory::instance().GetArrowShopItem( x, y, width, height, backgroundImage, price, restoreAmount );

								if( item->LoadItemImage() )
								{
									_pShop->AddItem( item );
								}
								else
								{
									ErrorSystem::instance().WriteError( "Shop Item failed to load" );
								}
							}

							else if( line.compare( 5, line.size() - 5, "HeartShopItem" ) == 0 )
							{
								int x = 0;
								int y = 0;
								int width = 0;
								int height = 0;
								int price = 0;
								int restoreAmount = 0;
								string backgroundImage = "";								

								for( int i = 0; i < 7; i++ )
								{
									getline( file, line );

									if( line.compare( 0, 4, "PosX" ) == 0 )
									{
										x = StringConverter::StringToInt( line.substr( 5 ), "xreadposx" );
									}
									else if( line.compare( 0, 4, "PosY" ) == 0 )
									{
										y = StringConverter::StringToInt( line.substr( 5 ), "xreadposy" );
									}
									else if( line.compare( 0, 5, "Width" ) == 0 )
									{
										width = StringConverter::StringToInt( line.substr( 6 ), "xreadwdth" );
									}
									else if( line.compare( 0, 6, "Height" ) == 0 )
									{
										height = StringConverter::StringToInt( line.substr( 7 ), "xreadheigh" );
									}
									else if( line.compare( 0, 5, "Price" ) == 0 )
									{
										price = StringConverter::StringToInt( line.substr( 6 ), "xreadprice" );
									}
									else if( line.compare( 0, 13, "RestoreAmount" ) == 0 )
									{
										restoreAmount = StringConverter::StringToInt( line.substr( 14 ), "xreadrestoreamount" );
									}
									else if( line.compare( 0, 15, "BackgroundImage" ) == 0 )
									{
										backgroundImage = line.substr( 16 );
									}
								}

								HeartShopItem* item = GameObjectFactory::instance().GetHeartShopItem( x, y, width, height, backgroundImage, price, restoreAmount );

								if( item->LoadItemImage() )
								{
									_pShop->AddItem( item );
								}
								else
								{
									ErrorSystem::instance().WriteError( "Shop Item failed to load" );
								}
							}
						}
					 }
				 }
			 }
		}
	}

	return true;
}

bool Level::LoadTiles()
{
	string imageLocation;

	//tile offsets
	int x = 0, y = 0;

	ifstream map( _LevelFile );

	if( map == NULL )
    {
        return false;    
    }
	
	int tileNumber = 1;
	
	if( map.is_open() )
	{
		bool binaryFound = false;
		string findLine;

		while( map.good() )
		{
			getline( map, findLine );

			if( !binaryFound && findLine.compare( "--Tiles--" ) == 0 )
			{
				binaryFound = true;
			}

			if( binaryFound )
			{
				//Initialize the tiles
				for( int t = 0; t < _TotalTiles; t++ )
				{
					//Determines what kind of tile will be made
					int tileType = -1;

					//Read tile from map file
					map >> tileType;

					if(tileType == 1)
					{
						imageLocation = _BlockTileTestImageLocation;
					}
					else
					{
						imageLocation = _TileTestImageLocation;
					}
        
					//If the was a problem in reading the map
					if( map.fail() == true )
					{
						//Stop loading map
						map.close();
						return false;
					}
 
					Tile* tile = new Tile( Initialize::Tile, tileNumber, x, y, LevelSystem::instance().GetCurrentLevel()->GetTileDimentions()->w, LevelSystem::instance().GetCurrentLevel()->GetTileDimentions()->h, tileType, imageLocation );
					TileObjectHolder::instance().AddObjectToReleventSectors( tile );

					//Move to next tile spot
					x += _pTileDimentions->w;
        
					//If we've gone too far
					if( x >= _pContainer->w )
					{
						//Move back
						x = 0;
            
						//Move to the next row
						y += _pTileDimentions->h;    
					}

					tileNumber++;

					//only draw in test mode
					if( Initialize::TestMode == true )
					{
						if( tile->LoadItemImage() == false )
						{
							return false;
						}
					}
				}

				break;
			}
		}
	}

	map.close();

	//laod image
	_pBackground = ImageLoader::instance().Load( _BackgroundFileLocation );

	if( _pBackground == NULL )
	{
		return false;
	}

	return true;
}

bool Level::LoadEnemies()
{
	ifstream file ( _LevelFile );

	if( file.is_open() )
	{
		string line;
		int lineReferance = 0; 
		bool enemiesFound = false;

		 while( file.good() )
		 {
			 getline( file, line );	
			  
			 if( !enemiesFound && line.compare( "--Enemies--" ) == 0 )
			 {
				 enemiesFound = true;
			 }

			 if( enemiesFound )
			 {			  
				if( line.compare( "------------------------------------" ) == 0 )
				{
					getline( file, line );	

					if( line.compare( 0, 6, "Object" ) == 0 )
					{	
						string tmp = line.substr( 7, line.size() - 7 );

						if( line.compare( 7, line.size() - 7, "Hagle" ) == 0 )
						{
							int x, y, width, height, startingAngle, movementSpeed, health, damage, areaOfSight;
							string spriteLocation;
							bool isHittable;

							for( int i = 0; i < 11; i++ )
							{
								getline( file, line );

								if( line.compare( 0, 4, "PosX" ) == 0 )
								{
									x = StringConverter::StringToInt( line.substr( 5 ), "xreadposx" );
								}
								else if( line.compare( 0, 4, "PosY" ) == 0 )
								{
									y = StringConverter::StringToInt( line.substr( 5 ), "xreadposy" );
								}
								else if( line.compare( 0, 5, "Width" ) == 0 )
								{
									width = StringConverter::StringToInt( line.substr( 6 ), "xreadwdth" );
								}
								else if( line.compare( 0, 6, "Height" ) == 0 )
								{
									height = StringConverter::StringToInt( line.substr( 7 ), "xreadheigh" );
								}
								else if( line.compare( 0, 13, "StartingAngle" ) == 0 )
								{
									startingAngle = StringConverter::StringToInt( line.substr( 14 ), "xreadangle" );
								}
								else if( line.compare( 0, 13, "MovementSpeed" ) == 0 )
								{
									movementSpeed = StringConverter::StringToInt( line.substr( 14 ), "xreadmovspd" );
								}
								else if( line.compare( 0, 14, "SpriteLocation" ) == 0 )
								{
									spriteLocation = line.substr( 15 );
								}
								else if( line.compare( 0, 6, "Health" ) == 0 )
								{
									health = StringConverter::StringToInt( line.substr( 7 ), "xreadhlth" );
								}
								else if( line.compare( 0, 10, "IsHittable" ) == 0 )
								{
									if( line.compare( 11, 15, "true" ) == 0 )
									{
										isHittable = true;
									}
									else
									{
										isHittable = false;
									}
								}
								else if( line.compare( 0, 6, "Damage" ) == 0 )
								{
									damage =  StringConverter::StringToInt( line.substr( 7 ), "xreaddmg" );
								}
								else if( line.compare( 0, 11, "AreaOfSight" ) == 0 )
								{
									areaOfSight =  StringConverter::StringToInt( line.substr( 12 ), "xreadsight" );
								}
								else
								{
									return false;
								}
							}
						 
							Hagle* hagle = GameObjectFactory::instance().GetHagle( x, y, width, height, startingAngle, movementSpeed, spriteLocation, health, isHittable, damage, areaOfSight );
							 
							GameObjectHolder::instance().AddToEntityContainer( hagle );
							GameObjectHolder::instance().AddObjectToReleventSectors( hagle );
						 }						
					 }
				 }
			 }
		 }

		 file.close();
	 }
	 else
	 {
		 //put stop code
		 return false;
	 }

	return true;
}

bool Level::LoadObjects()
{
	ifstream file ( _LevelFile );

	if( file.is_open() )
	{
		string line;
		int lineReferance = 0; 
		bool enemiesFound = false;

		 while( file.good() )
		 {
			 getline( file, line );	
			  
			 if( !enemiesFound && line.compare( "--Enemies--" ) == 0 )
			 {
				 enemiesFound = true;
			 }

			 if( enemiesFound )
			 {			  
				if( line.compare( "------------------------------------" ) == 0 )
				{
					getline( file, line );	

					if( line.compare( 0, 6, "Object" ) == 0 )
					{
							
						string tmp = line.substr( 7, line.size() - 7 );

						/* --------------------------------------- Door Object --------------------------------------------- */
						if( line.compare( 7, line.size() - 7, "Door" ) == 0 )
						{
							int x = 0;
							int y = 0;
							int width = 0;
							int height = 0;
							int startingAngle = 0;
							string spriteLocation;
							string forwardLevel;
							string entryPointID;

							for( int i = 0; i < 10; i++ )
							{
								getline( file, line );

								if( line.compare( 0, 4, "PosX" ) == 0 )
								{
									x = StringConverter::StringToInt( line.substr( 5 ), "xreadposx" );
								}
								else if( line.compare( 0, 4, "PosY" ) == 0 )
								{
									y = StringConverter::StringToInt( line.substr( 5 ), "xreadposy" );
								}
								else if( line.compare( 0, 5, "Width" ) == 0 )
								{
									width = StringConverter::StringToInt( line.substr( 6 ), "xreadwdth" );
								}
								else if( line.compare( 0, 6, "Height" ) == 0 )
								{
									height = StringConverter::StringToInt( line.substr( 7 ), "xreadheigh" );
								}
								else if( line.compare( 0, 13, "StartingAngle" ) == 0 )
								{
									startingAngle = StringConverter::StringToInt( line.substr( 14 ), "xreadangle" );
								}
								else if( line.compare( 0, 14, "SpriteLocation" ) == 0 )
								{
									spriteLocation = line.substr( 15 );
								}
								else if( line.compare( 0, 12, "ForwardLevel" ) == 0 )
								{
									forwardLevel = line.substr( 13 );
								}
								else if( line.compare( 0, 12, "EntryPointID" ) == 0 )
								{
									entryPointID = line.substr( 13 );
								}
							}

							Door* door = GameObjectFactory::instance().GetDoor( x, y, width, height, startingAngle, spriteLocation, forwardLevel, entryPointID );
							 
							GameObjectHolder::instance().AddToEntityContainer( door );
							GameObjectHolder::instance().AddObjectToReleventSectors( door );
						}
						/* --------------------------------------- Beacon Object --------------------------------------------- */
						if( line.compare( 7, line.size() - 7, "Beacon" ) == 0 )
						{
							int x = 0;
							int y = 0;
							int width = 0;
							int height = 0;
							int startingAngle = 0;
							string spriteLocation;							
							string entryPointID;

							for( int i = 0; i < 7; i++ )
							{
								getline( file, line );

								if( line.compare( 0, 4, "PosX" ) == 0 )
								{
									x = StringConverter::StringToInt( line.substr( 5 ), "xreadposx" );
								}
								else if( line.compare( 0, 4, "PosY" ) == 0 )
								{
									y = StringConverter::StringToInt( line.substr( 5 ), "xreadposy" );
								}
								else if( line.compare( 0, 5, "Width" ) == 0 )
								{
									width = StringConverter::StringToInt( line.substr( 6 ), "xreadwdth" );
								}
								else if( line.compare( 0, 6, "Height" ) == 0 )
								{
									height = StringConverter::StringToInt( line.substr( 7 ), "xreadheigh" );
								}
								else if( line.compare( 0, 13, "StartingAngle" ) == 0 )
								{
									startingAngle = StringConverter::StringToInt( line.substr( 14 ), "xreadangle" );
								}
								else if( line.compare( 0, 14, "SpriteLocation" ) == 0 )
								{
									spriteLocation = line.substr( 15 );
								}
								else if( line.compare( 0, 12, "EntryPointID" ) == 0 )
								{
									entryPointID = line.substr( 13 );
								}
							}

							Beacon* beacon = GameObjectFactory::instance().GetBeacon( entryPointID, x, y, width, height, startingAngle, spriteLocation );
							 
							GameObjectHolder::instance().AddToEntityContainer( beacon );
							GameObjectHolder::instance().AddObjectToReleventSectors( beacon );
						}
						/* --------------------------------------- Tree Object --------------------------------------------- */
						if( line.compare( 7, line.size() - 7, "Tree" ) == 0 )
						{
							int x = 0;
							int y = 0;
							int width = 0;
							int height = 0;
							string spriteLocation;					

							for( int i = 0; i < 5; i++ )
							{
								getline( file, line );

								if( line.compare( 0, 4, "PosX" ) == 0 )
								{
									x = StringConverter::StringToInt( line.substr( 5 ), "xreadposx" );
								}
								else if( line.compare( 0, 4, "PosY" ) == 0 )
								{
									y = StringConverter::StringToInt( line.substr( 5 ), "xreadposy" );
								}
								else if( line.compare( 0, 5, "Width" ) == 0 )
								{
									width = StringConverter::StringToInt( line.substr( 6 ), "xreadwdth" );
								}
								else if( line.compare( 0, 6, "Height" ) == 0 )
								{
									height = StringConverter::StringToInt( line.substr( 7 ), "xreadheigh" );
								}
								else if( line.compare( 0, 14, "SpriteLocation" ) == 0 )
								{
									spriteLocation = line.substr( 15 );
								}
							}

							BigTree* tree = GameObjectFactory::instance().GetBigTree( x, y, width, height, spriteLocation );
							tree->SetMovable( false );

							GameObjectHolder::instance().AddToBlockerContainer( tree );
							GameObjectHolder::instance().AddObjectToReleventSectors( tree );
						}
						/* --------------------------------------- Spike Trap Object --------------------------------------------- */
						if( line.compare( 7, line.size() - 7, "SpikeTrap" ) == 0 )
						{
							int x = 0;
							int y = 0;
							int width = 0;
							int height = 0;
							string spriteLocation;				
							int activePeriod;
							int damage = 0;

							for( int i = 0; i < 7; i++ )
							{
								getline( file, line );

								if( line.compare( 0, 4, "PosX" ) == 0 )
								{
									x = StringConverter::StringToInt( line.substr( 5 ), "xreadposx" );
								}
								else if( line.compare( 0, 4, "PosY" ) == 0 )
								{
									y = StringConverter::StringToInt( line.substr( 5 ), "xreadposy" );
								}
								else if( line.compare( 0, 5, "Width" ) == 0 )
								{
									width = StringConverter::StringToInt( line.substr( 6 ), "xreadwdth" );
								}
								else if( line.compare( 0, 6, "Height" ) == 0 )
								{
									height = StringConverter::StringToInt( line.substr( 7 ), "xreadheigh" );
								}
								else if( line.compare( 0, 14, "SpriteLocation" ) == 0 )
								{
									spriteLocation = line.substr( 15 );
								}
								else if( line.compare( 0, 12, "ActivePeriod" ) == 0 )
								{
									activePeriod = StringConverter::StringToInt( line.substr( 13 ), "xreadactivePeriod" );
								}
								else if( line.compare( 0, 6, "Damage" ) == 0 )
								{
									damage =  StringConverter::StringToInt( line.substr( 7 ), "xreaddmg" );
								}
							}

							SpikeTrap* trap = GameObjectFactory::instance().GetSpikeTrap( x, y, width, height, spriteLocation, activePeriod, damage );
							trap->SetMovable( false );

							GameObjectHolder::instance().AddToEntityContainer( trap );
							GameObjectHolder::instance().AddObjectToReleventSectors( trap );
						}
						/* --------------------------------------- Grass Object --------------------------------------------- */
						if( line.compare( 7, line.size() - 7, "Grass" ) == 0 )
						{
							int x = 0;
							int y = 0;
							int width = 0;
							int height = 0;
							string spriteLocation;			

							for( int i = 0; i < 7; i++ )
							{
								getline( file, line );

								if( line.compare( 0, 4, "PosX" ) == 0 )
								{
									x = StringConverter::StringToInt( line.substr( 5 ), "xreadposx" );
								}
								else if( line.compare( 0, 4, "PosY" ) == 0 )
								{
									y = StringConverter::StringToInt( line.substr( 5 ), "xreadposy" );
								}
								else if( line.compare( 0, 5, "Width" ) == 0 )
								{
									width = StringConverter::StringToInt( line.substr( 6 ), "xreadwdth" );
								}
								else if( line.compare( 0, 6, "Height" ) == 0 )
								{
									height = StringConverter::StringToInt( line.substr( 7 ), "xreadheigh" );
								}
								else if( line.compare( 0, 14, "SpriteLocation" ) == 0 )
								{
									spriteLocation = line.substr( 15 );
								}
							}

							Grass* grass = GameObjectFactory::instance().GetGrass( x, y, width, height, spriteLocation );
							grass->SetMovable( false );

							GameObjectHolder::instance().AddToEntityContainer( grass );
							GameObjectHolder::instance().AddObjectToReleventSectors( grass );
						}

						/* --------------------------------------- House Object --------------------------------------------- */
						if( line.compare( 7, line.size() - 7, "House" ) == 0 )
						{
							int x = 0;
							int y = 0;
							int width = 0;
							int height = 0;
							int doorX = 0;
							int doorY = 0;
							int doorWidth = 0;
							int doorHeight = 0;
							string spriteLocation;
							string forwardLevel;
							string entryPointID;

							for( int i = 0; i < 13; i++ )
							{
								getline( file, line );

								if( line.compare( 0, 4, "PosX" ) == 0 )
								{
									x = StringConverter::StringToInt( line.substr( 5 ), "xreadposx" );
								}
								else if( line.compare( 0, 4, "PosY" ) == 0 )
								{
									y = StringConverter::StringToInt( line.substr( 5 ), "xreadposy" );
								}
								else if( line.compare( 0, 5, "Width" ) == 0 )
								{
									width = StringConverter::StringToInt( line.substr( 6 ), "xreadwdth" );
								}
								else if( line.compare( 0, 6, "Height" ) == 0 )
								{
									height = StringConverter::StringToInt( line.substr( 7 ), "xreadheigh" );
								}
								else if( line.compare( 0, 8, "DoorPosX" ) == 0 )
								{
									doorX = StringConverter::StringToInt( line.substr( 9 ), "xreadposx" );
								}
								else if( line.compare( 0, 8, "DoorPosY" ) == 0 )
								{
									doorY = StringConverter::StringToInt( line.substr( 9 ), "xreadposy" );
								}
								else if( line.compare( 0, 9, "DoorWidth" ) == 0 )
								{
									doorWidth = StringConverter::StringToInt( line.substr( 10 ), "xreadwdth" );
								}
								else if( line.compare( 0, 10, "DoorHeight" ) == 0 )
								{
									doorHeight = StringConverter::StringToInt( line.substr( 11 ), "xreadheigh" );
								}
								else if( line.compare( 0, 14, "SpriteLocation" ) == 0 )
								{
									spriteLocation = line.substr( 15 );
								}
								else if( line.compare( 0, 12, "ForwardLevel" ) == 0 )
								{
									forwardLevel = line.substr( 13 );
								}
								else if( line.compare( 0, 12, "EntryPointID" ) == 0 )
								{
									entryPointID = line.substr( 13 );
								}
							}

							House* house = GameObjectFactory::instance().GetHouse( x, y, width, height, spriteLocation, doorX, doorY, doorWidth, doorHeight , forwardLevel, entryPointID );
							 
							GameObjectHolder::instance().AddToEntityContainer( house );
							GameObjectHolder::instance().AddObjectToReleventSectors( house );
						}
						
						/* --------------------------------------- ShopSpot Object --------------------------------------------- */
						if( line.compare( 7, line.size() - 7, "ShopSpot" ) == 0 )
						{
							int x = 0;
							int y = 0;
							int width = 0;
							int height = 0;
							string spriteLocation;														

							for( int i = 0; i < 5; i++ )
							{
								getline( file, line );

								if( line.compare( 0, 4, "PosX" ) == 0 )
								{
									x = StringConverter::StringToInt( line.substr( 5 ), "xreadposx" );
								}
								else if( line.compare( 0, 4, "PosY" ) == 0 )
								{
									y = StringConverter::StringToInt( line.substr( 5 ), "xreadposy" );
								}
								else if( line.compare( 0, 5, "Width" ) == 0 )
								{
									width = StringConverter::StringToInt( line.substr( 6 ), "xreadwdth" );
								}
								else if( line.compare( 0, 6, "Height" ) == 0 )
								{
									height = StringConverter::StringToInt( line.substr( 7 ), "xreadheigh" );
								}								
								else if( line.compare( 0, 14, "SpriteLocation" ) == 0 )
								{
									spriteLocation = line.substr( 15 );
								}								
							}

							ShopSpot* shopSpot= GameObjectFactory::instance().GetShopSpot( x, y, width, height, spriteLocation );
							 
							GameObjectHolder::instance().AddToEntityContainer( shopSpot);
							GameObjectHolder::instance().AddObjectToReleventSectors( shopSpot );
						}
					}
				}
			 }
		 }
	}

	return true;
}

bool Level::LoadAsStartScreen()
{
	/*--------------------------- Put Errors in Read ----------------------------*/
	ifstream file ( _LevelFile );

	if( file.is_open() )
	{
		string line;
		int lineReferance = 0; 
		bool propsFound = false;

		 while( file.good() )
		 {
			 getline( file, line );	
			  
			 if( !propsFound && line.compare( "--Properties--" ) == 0 )
			 {
				 propsFound = true;
			 }

			 if( propsFound )
			 {
				 if( line.compare( 0, 2, "id" ) == 0 )
				 {
					 _levelID = line.substr( 3 );
				 }
				 else if( line.compare( 0, 5, "width" ) == 0 )
				 {
					 _pContainer->w = StringConverter::StringToInt( line.substr( 6 ), "Error - LevelWidthRead" );
				 }
				 else if( line.compare( 0, 6, "height" ) == 0 )
				 {
					 _pContainer->h = StringConverter::StringToInt( line.substr( 7 ), "Error - LevelHeightRead" );
				 }
				 else if( line.compare( 0, 22, "backgroundfilelocation" ) == 0 )
				 {
					 _BackgroundFileLocation = line.substr( 23 );
				 }
				 else if( line.compare( 0, 10, "startlevel" ) == 0 )
				 {
					 LevelSystem::instance().SetNextLevelFileLocation( line.substr( 11 ) );
				 }
				 else if( line.compare( 0, 12, "entrypointid" ) == 0 )
				 {
					 LevelSystem::instance().SetNextLevelEntryPointID( line.substr( 13 ) );
				 }
			 }
		 }
	}

	file.close();

	_pBackground = ImageLoader::instance().Load( _BackgroundFileLocation );

	if( _pBackground == NULL )
	{
		ErrorSystem::instance().WriteError( "Error Loading welcome background file" );
		return false;
	}

	return true;
}


SDL_Rect* Level::GetContainer() const
{
	return _pContainer;
}

SDL_Rect* Level::GetTileDimentions() const
{
	return _pTileDimentions;
}

bool Level::NextLevel()
{
	return true;
}

void Level::PaintBackground( MainWnd* window, SDL_Rect* camora )
{
	SDL_Rect location;
	location.x = 0;
	location.y = 0;

	window->RenderToScreen( _pBackground, &location, camora );
}

Shop* Level::GetShop()
{
	return _pShop;
}