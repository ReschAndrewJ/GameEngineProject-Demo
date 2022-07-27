#ifndef ENEMY_C
#define ENEMY_C

#include "../EnemyA/EnemyA.h"
#include "../Timer/Timer.h"


const auto OBJECT_CLASS_ENEMY_C = "EnemyC";

const auto ATTRIBUTE_ENEMY_C_ATTACK_DELAY = ATTRIBUTE_TIMER_LENGTH;
const auto ATTRIBUTE_ENEMY_C_BULLET_FILEPATH = "EnemyCBulletFile";
const auto ATTRIBUTE_ENEMY_C_BULLET_IDENTIFIER = "EnemyCBulletId";

const auto ATTRIBUTE_ENEMY_C_BULLET_DIRECTION_X = "EnemyCBulletDirectionX";
const auto ATTRIBUTE_ENEMY_C_BULLET_DIRECTION_Y = "EnemyCBulletDirectionY";
const auto ATTRIBUTE_ENEMY_C_BULLET_DIRECTION_Z = "EnemyCBulletDirectionZ";

const auto ATTRIBUTE_ENEMY_C_ON_COOLDOWN = "EnemyCOnCooldown";

class EnemyC : public virtual EnemyA, public virtual Timer {
public:
	EnemyC();
	virtual ~EnemyC();

	static void process_func(Object*, float);
};


#endif