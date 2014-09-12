#ifndef _LOGICENGINE_
#define _LOGICENGINE_

class LogicEngine
{
public:

	LogicEngine();
	~LogicEngine();

	SDL_Event event;

	bool Initialize();	
	bool Quit();
	bool GameLoop();
	bool CollisionCheck( GameObject* object );
	bool ItemCollisionCheck( Character* character );
	void LevelSwitch();

private:

	bool _Quit;

	int _CurrentGameState;
	int _StateTracker;

	GameTimer* _pGameTimer;
	MainWnd* _pMainWnd;
	Camora* _pCamora;
	CharacterDisplaySystem* _pCharacterDisplaySystem;
	InventorySystem* _pInventorySystem;
	RupeeDisplay* _RupeeDisplay;
	ArrowDisplay* _ArrowDisplay;

	vector<GameObject*>* tmpList;

	void HandleEvents();
	void UpdateObjects();
	void PlayerCollisionDetection();
	void Draw();
	void DrawStartScreen();
	void DetermineGameState();
	void BuildCollisionList( GameObject* object, vector<GameObject*>* allObjectsInSector, vector<GameObject*>* collisionList );
	void SortList( vector<GameObject*>* listToSort );

	void InsertIntoList( GameObject* object, vector<GameObject*>* list, int possition );
};

#endif
