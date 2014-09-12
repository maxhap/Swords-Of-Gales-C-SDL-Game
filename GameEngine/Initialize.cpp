#include "stdafx.h"					

using namespace std;

typedef basic_string<char,char_traits<char>,allocator<char> > const  INIT;

INIT Initialize::ErrorLogLocation = "Logs\\Errors.txt";
INIT Initialize::EventLogLocation = "Logs\\Events.txt";

INIT Initialize::StartScreenFileLocatin = "LevelFiles\\welcomescreen.txt";
INIT Initialize::StartLevel = "LevelFiles\\level1.txt";

INIT Initialize::CharacterSpriteLocation = "Sprites\\Player.png";
INIT Initialize::InventorySystemBackgroundLocation = "InventorySystemFiles\\background.png";
INIT Initialize::InventorySystemActiveBackgroundLocation = "InventorySystemFiles\\background_active.png";

INIT Initialize::InventoryItemSwordImageLocation = "InventorySystemFiles\\master_sword.png";
INIT Initialize::InventoryItemSwordActiveImageLocation = "InventorySystemFiles\\master_sword_active.png";
INIT Initialize::InventoryItemBowArrowImageLocation = "InventorySystemFiles\\bow_arrow.png";
INIT Initialize::InventoryItemBowArrowActiveImageLocation = "InventorySystemFiles\\bow_arrow_active.png";

INIT Initialize::DisplaySystemBackgroundLocation = "CharacterDisplayFiles\\background.png";

INIT Initialize::FullHeartBackgroundLocation = "CharacterDisplayFiles\\full_heart.png";
INIT Initialize::ThreeHeartBackgroundLocation = "CharacterDisplayFiles\\three_quater_heart.png";
INIT Initialize::HalfHeartBackgroundLocation = "CharacterDisplayFiles\\half_heart.png";
INIT Initialize::OneHeartBackgroundLocation = "CharacterDisplayFiles\\one_quater_heart.png";

INIT Initialize::ArrowSpriteLocation = "Sprites\\arrow.png";

INIT Initialize::GameHeartImageLocation = "Sprites\\heart.png";

INIT Initialize::InventoryItemRedPotionImageLocation = "InventorySystemFiles\\red_potion.png";
INIT Initialize::GameRedPotionImageLocation = "Sprites\\red_potion.png";
INIT Initialize::GameGreenRupeeImageLocation = "Sprites\\green_rupee.png";

INIT Initialize::RupeeDisplayImageLocation = "InventorySystemFiles\\green_rupee.png";
INIT Initialize::ArrowDisplayImageLocation = "InventorySystemFiles\\arrow.png";