// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>

// TODO: reference additional headers your program requires here

#define _USE_MATH_DEFINES

#include <iostream>

#include "SDL.h"
#include "SDL_opengl.h"
#include "SDL_image.h"
#include "SDL_draw.h"
#include "SDL_ttf.h"
#include <gl/gl.h>
#include <gl/glu.h>
#include <cmath>
#include <string>
#include <sstream>
#include <cmath>
#include <vector>
#include <fstream>
#include <algorithm>
#include <map>

//Initialize
#include "Initialize.h"

//templates
#include "Singleton.h"

//Misc
#include "ErrorSystem.h"
#include "MemoryManagement.h"
#include "GameEvent.h"
#include "EventManager.h"
#include "StringConverter.h"
#include "Point.h"
#include "GraphicsTexture.h"

//Timers
#include "GameTimer.h"

//Windows
#include "Camora.h"
#include "MainWnd.h"
#include "ImageLoader.h"

//ObjectHolder
#include "GameSector.h"
#include "GameObjectHolder.h"
#include "TileObjectHolder.h"

//GameObjects
#include "Interactable.h"
#include "ArtificialIntelligence.h"
#include "Hittable.h"
#include "Health.h"
#include "Object.h"
#include "GameObject.h"
#include "InteractableGameObject.h"
#include "Character.h"
#include "Player.h"

#include "Tile.h"

#include "Door.h"
#include "Beacon.h"
#include "BigTree.h"
#include "Grass.h"
#include "House.h"

//traps
#include "Trap.h"
#include "SpikeTrap.h"

//enemies
#include "MeeleEnemy.h"
#include "Hagle.h"

//items
#include "Item.h"
#include "Heart.h"
#include "RedPotion.h"
#include "GreenRupee.h"
#include "ArrowDisplay.h"

#include "ItemHandler.h"

//inventory 
#include "InventoryHolder.h"
#include "InventoryItem.h"
#include "SwordAttackInventoryItem.h"
#include "InventoryItemHolder.h"

#include "InventoryRedPotion.h"

//display
#include "DisplayHolder.h"
#include "HealthHeart.h"
#include "CharacterDisplaySystem.h"
#include "RupeeDisplay.h"

//attacks
#include "Projectile.h"
#include "Attack.h"
#include "SwordAttack.h"
#include "AttackModuleHolder.h"
#include "Arrow.h"
#include "BowArrow.h"

//systems
#include "InventorySystem.h"
#include "CombatSystem.h"

//Logic
#include "GameState.h"
#include "LogicEngine.h"

//level system
#include "ExitPoint.h"
#include "EntryPoint.h"
#include "Level.h"
#include "LevelSystem.h"

#include "ShopItem.h"
#include "ArrowShopItem.h"
#include "HeartShopItem.h"
#include "Shop.h"
#include "ShopSpot.h"

//factories
#include "GameObjectFactory.h"