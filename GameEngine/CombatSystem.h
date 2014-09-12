#ifndef _COMBATSYSTEM_
#define _COMBATSYSTEM_

#include "stdafx.h"

class LogicEngine;
class Projectiles;
class MeeleEnemy;

class CombatSystem : public Singleton<CombatSystem>
{

public:

	~CombatSystem();

	void AddInventorySystem( InventorySystem* inventorySystem );
	void HandleEvent( SDL_Event event );
	void DrawTestAreas( MainWnd* window, Camora* camora );
	void CreateArrow( Attack* attack );
	void Update();
	void DrawProjectiles( MainWnd* window, Camora* camora );
	void ProcessAttackOnPlayer( Attack* attack );

	vector<GameObject*>* GetHitList( Projectile* attack );
	vector<GameObject*>* GetHitList( Attack* attack );

private:

	CombatSystem();

	friend class Singleton<CombatSystem>;

	InventorySystem* _InventorySystem;
	vector<Projectile*>* _pProjectileHolder;
	
	void ProcessAttack();
	void UpdateProjectiles();



};


#endif