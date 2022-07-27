#include "Enemy.h"

#include "../../General/CollisionMaskEnums.h"

Enemy::Enemy() {
	addClassIdentifier(OBJECT_CLASS_ENEMY);

	setAttribute(ATTRIBUTE_COLLIDER_MASK_OWN, 
		(int)getAttribute(ATTRIBUTE_COLLIDER_MASK_OWN) | (int)Collision_Masks::ENEMY);
	setAttribute(ATTRIBUTE_COLLIDER_MASK_TARGET, 
		(int)getAttribute(ATTRIBUTE_COLLIDER_MASK_TARGET) | (int)Collision_Masks::BULLET_PLAYER);

	addProcessFunction(&processFunc, 5);
}
Enemy::~Enemy() {}

