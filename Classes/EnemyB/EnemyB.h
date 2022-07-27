#ifndef ENEMY_B
#define ENEMY_B

#include "../EnemyA/EnemyA.h"
#include "../Timer/Timer.h"

const auto OBJECT_CLASS_ENEMY_B = "EnemyB";

const auto ATTRIBUTE_ENEMY_B_ATTACK_DELAY = ATTRIBUTE_TIMER_LENGTH;
const auto ATTRIBUTE_ENEMY_B_BULLET_FILEPATH = "EnemyBBulletFile";
const auto ATTRIBUTE_ENEMY_B_BULLET_IDENTIFIER = "EnemyBBulletId";

const auto ATTRIBUTE_ENEMY_B_ON_COOLDOWN = "EnemyBOnCooldown";

class EnemyB : public virtual EnemyA, public virtual Timer {
public:
	EnemyB();
	virtual ~EnemyB();
	
	static void process_func(Object*, float);
};

#endif