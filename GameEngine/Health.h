#ifndef _HEALTH_
#define _HEALTH_

class Health 
{

public:

	Health( int maxHealth, int healthAmount );
	~Health();

	int GetCurrentHealth();
	int GetMaxHealth();
	void ReduceHealth( int damage );
	void RestoreHealth( int recovery );

protected:

	int _CurrentHealth;
	int _MaxHealth;

};


#endif