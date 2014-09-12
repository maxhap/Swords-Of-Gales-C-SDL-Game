#ifndef _INITIALIZE_
#define _INITIALIZE_

using namespace std;

class Initialize
{

public:

	//testmode
	static const bool TestMode = false;

	//logs
	static const string ErrorLogLocation;
	static const string EventLogLocation;

	//gamespeed
	static const int FRAMERATE = 60;
	static const int RunAnimationRate = 15;
	static const int AttackAnimationRate = 2;

	//Attributes of screen dont change
	static const int SCREEN_WIDTH = 800;
	static const int SCREEN_HEIGHT = 600;
	static const int SCREEN_BPP = 32;

	static const int BattleGroundWidth = 800;
	static const int BattleGroundHeight = 600;//450;

	//Object Types
	static const int Blocker = 1000;
	static const int Entity = 1001;

	static const int Unset = -1;
	static const int Player = 0;
	static const int Tile = 1;
	static const int Arrow = 2;
	static const int Hagle = 3;
	static const int Door = 4;
	static const int Beacon = 5;

	static const int Potion = 6;
	static const int Rupee = 7;
	static const int Heart = 8;

	static const int BigTree = 9;
	static const int SpikeTrap = 10;
	static const int Grass = 11;
	static const int House = 12;
	static const int ShopSpot = 13;
	static const int Shop = 14;


	static const int ArrowShopItem = 100;

	//Character Display
	static const int DisplaySystemXPosition = 0;
	static const int DisplaySystemYPosition = 0;	
	static const int DisplaySystemWidth = BattleGroundWidth;
	static const int DisplaySystemHeight = 50;
	static const string DisplaySystemBackgroundLocation;

	static const int Heart100ID = 0;
	static const int Heart34ID = 1;
	static const int Heart12ID = 2;
	static const int Heart14ID = 3;

	static const int HeartWidth = 26;
	static const int HeartHeight = 20;

	static const string FullHeartBackgroundLocation;
	static const string ThreeHeartBackgroundLocation;
	static const string HalfHeartBackgroundLocation;
	static const string OneHeartBackgroundLocation;

	static const int RupeeDisplayX = ( int ) ( BattleGroundWidth - 45 );
	static const int RupeeDisplayY = ( int ) ( BattleGroundHeight - 42 );
	static const int RupeeDisplayWidth = 45;
	static const int RupeeDisplayHeight = 40;
	static const string RupeeDisplayImageLocation;

	static const int ArrowDisplayX = ( int ) ( BattleGroundWidth - 100 );
	static const int ArrowDisplayY = ( int ) ( BattleGroundHeight - 42 );
	static const int ArrowDisplayWidth = 25;
	static const int ArrowDisplayHeight = 40;
	static const string ArrowDisplayImageLocation;


	//character attributes
	static const int CharacterMaxHealth = 40;
	static const int CharacterStartingArrows = 100;

	//inventory system	
	static const int InventorySystemWidth = BattleGroundWidth ;//( int ) ( BattleGroundWidth * 0.7 );
	static const int InventorySystemHeight = 50;
	static const int InventorySystemXPosition = 0;
	static const int InventorySystemYPosition = BattleGroundHeight -InventorySystemHeight;

	static const int InventorySystemCopacity = 4;
	static const string InventorySystemBackgroundLocation;
	static const string InventorySystemActiveBackgroundLocation;

	//inventory items
	static const int InventoryItemWidth = 95;
	static const int InventoryItemHeight = 48;
	//sword item	
	static const string InventoryItemSwordImageLocation;
	static const string InventoryItemSwordActiveImageLocation;
	//bowarrow
	static const string InventoryItemBowArrowImageLocation;
	static const string InventoryItemBowArrowActiveImageLocation;
	//oother inventory items
	static const string InventoryItemRedPotionImageLocation;

	//game items
	static const string GameHeartImageLocation;
	static const string GameRedPotionImageLocation;
	static const string GameGreenRupeeImageLocation;

	//level
	static const string StartScreenFileLocatin;
	static const string StartLevel;

	static const int SectorDevisionValue = 4;

	//Tiles
	static const int TileTypePlain = 0;
	static const int TileTypleWall = 1;

	//animationType
	static const int AnimationRun = 0;
	static const int AnimationSwordAttack = 1;
	static const int AnimationBowArrow = 2;

	//character
	static const int SpriteWidth = 800;
	static const int SpriteHeight = 320;
	static const int CharacterWidth = 48;
	static const int CharacterHeight = 48;
	static const int CharacterSpriteImagePadding = 0; 
	static const string CharacterSpriteLocation;

	//character movement
	//0 for block movement 1 for rotation
	static const int CompasMovement = 0;
	static const int RotationMovement = 1;

	static const int CurrentMovementType = CompasMovement;
	static const int RotationSpeed = 7;
	static const int RotationAcceleration = 45;
	static const int MovementSpeed = 8;

	//character sprite Compasbased direction
	static const int SpriteDownMotion = 0;
	static const int SpriteUpMotion = 1;
	static const int SpriteLeftMotion = 2;
	static const int SpriteRightMotion = 3;

	static const int SpriteSwordDown = 4;
	static const int SpriteSwordUp= 5;
	static const int SpriteSwordLeft = 6;
	static const int SpriteSwordRight = 7;

	static const int SpriteBowArrowDown = 8;
	static const int SpriteBowArrowUp= 9;
	static const int SpriteBowArrowLeft = 10;
	static const int SpriteBowArrowRight = 11;
	
	//arrow
	static const string ArrowSpriteLocation;
	static const int ArrowWidth = 50;
	static const int ArrowHeight = 50;
	static const int ArrowSpeed = 22;
	static const int ArrowMaxTravelDistance = 500;	

	//attacks
	static const int SwordAttack = 100;
	static const int BowArrowAttack= 101;
};

#endif