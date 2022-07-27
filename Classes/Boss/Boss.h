#ifndef BOSS
#define BOSS

#include "../EnemyA/EnemyA.h"

const auto OBJECT_CLASS_BOSS = "Boss";

const auto ATTRIBUTE_BOSS_MIN_X = "BossMinX";
const auto ATTRIBUTE_BOSS_MAX_X = "BossMaxX";
const auto ATTRIBUTE_BOSS_MIN_Y = "BossMinY";
const auto ATTRIBUTE_BOSS_MAX_Y = "BossMaxY";
const auto ATTRIBUTE_BOSS_MIN_Z = "BossMinZ";
const auto ATTRIBUTE_BOSS_MAX_Z = "BossMaxZ";

const auto ATTRIBUTE_BOSS_BASE_SPEED = "BossSpeed";

class Boss : public virtual EnemyA {
public:
	Boss();
	virtual ~Boss();

	void getMovementDirection(float movementSlope[3]) const override;

	static void afterCreation_func(Object*);
	static void process_func(Object*, float);

	void Bullet_onCollision() override;

private:
	float targetPos[3]{};

	void randomizeTargetPos();
};


#endif 