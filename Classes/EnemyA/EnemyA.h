#ifndef ENEMY_A
#define ENEMY_A

#include "../Enemy/Enemy.h"
#include "../Bullet/Bullet.h"

const auto OBJECT_CLASS_ENEMY_A = "EnemyA";

class EnemyA : public virtual Enemy, public virtual Bullet {
public:
	EnemyA();
	virtual ~EnemyA();


	void getMovementDirection(float movementSlope[3]) const override;

	void Bullet_onCollision() override;

};



#endif