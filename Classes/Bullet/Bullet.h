#ifndef OBJECT_BULLET
#define OBJECT_BULLET

#include "GameEngineLib/Objects/Collision/Object_Collision.h"

const auto OBJECT_CLASS_BULLET = "Bullet";

// the amount of damage a bullet deals when it lands
const auto ATTRIBUTE_BULLET_DAMAGE = "BulletPower";
// the length of time after hitting a target that that target is invulnerable for, in seconds
// in general, enemy bullets should grant longer iTime than player bullets
const auto ATTRIBUTE_BULLET_ITIME = "BulletITime";

class Bullet : public virtual Object_Collision {
public:
	Bullet();
	virtual ~Bullet();

	// perform actions such as immediate despawn (default behavior) or bullet splitting
	virtual void Bullet_onCollision() = 0;
};


#endif // OBJECT_BULLET