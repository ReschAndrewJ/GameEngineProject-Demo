#ifndef PLAYER_TYPE_A
#define PLAYER_TYPE_A

#include "../Player/Player.h"

// attacks with typeABullet 

const auto OBJECT_CLASS_PLAYER_TYPE_A = "Player_TypeA";

const auto ATTRIBUTE_PLAYER_TYPE_A_BULLET_FILEPATH = "PlayerTypeABulletFile";
const auto ATTRIBUTE_PLAYER_TYPE_A_BULLET_IDENTIFIER = "PlayerTypeABulletId";

const auto ATTRIBUTE_PLAYER_TYPE_A_BULLET_COOLDOWN = "PlayerTypeACooldown";
const auto ATTRIBUTE_PLAYER_TYPE_A_COOLDOWN_REMAINING = "PlayerTypeACooldownRemaining";
const auto ATTRIBUTE_PLAYER_TYPE_A_BULLET_FIRE_SOUND = "PlayerTypeABulletFireSound";

class Player_TypeA : public virtual Player {
private:
	Input_Handler* inputHandlerPtr;

public:
	Player_TypeA();
	virtual ~Player_TypeA();

	static void processFunc(Object*, float);

protected:
	void doAttacks() override;

};


#endif