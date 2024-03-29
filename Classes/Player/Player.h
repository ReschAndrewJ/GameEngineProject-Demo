#ifndef OBJECT_PLAYER
#define OBJECT_PLAYER

#include "../LiveEntity/LiveEntity.h"

#include "../../_GameEngineSrc/Engines/Main/Input_Handler.h"


const auto OBJECT_CLASS_PLAYER = "Player";

const auto ATTRIBUTE_PLAYER_DAMAGE_SOUND = "PlayerDamageSound";

class Player : public virtual LiveEntity {
private:
	Input_Handler* inputHandlerPtr; 

public:
	Player();
	virtual ~Player();

	static void processFunc(Object*, float);

protected:
	// check if an attack condition is met and use that attack
	virtual void doAttacks();
	
	void onDamage() override;

	void onDeath() override;

protected:
	void getMovementDirection(float move[3]) const override;

	//void onDeath() override;
	

};

#endif // OBJECT_PLAYER