#ifndef TYPE_A_BULLET
#define TYPE_A_BULLET

#include "../Bullet/Bullet.h"

// A basic projectile,

const auto OBJECT_CLASS_TYPE_A_BULLET = "TypeABullet";

const auto ATTRIBUTE_TYPE_A_BULLET_COLLISION_SOUND_FILE = "TypeABulletHitSoundFile";
const auto ATTRIBUTE_TYPE_A_BULLET_DIRECTION_X = "TypeABulletDirectionX";
const auto ATTRIBUTE_TYPE_A_BULLET_DIRECTION_Y = "TypeABulletDirectionY";
const auto ATTRIBUTE_TYPE_A_BULLET_DIRECTION_Z = "TypeABulletDirectionZ";
const auto ATTRIBUTE_TYPE_A_BULLET_SPEED = "TypeABulletSpeed";

class TypeABullet : public virtual Bullet {
public:
	TypeABullet();
	virtual ~TypeABullet();
	
	static void process_func(Object*, float);

	void Bullet_onCollision() override;
};


#endif