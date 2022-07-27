#include "EnemyA.h"

#include "../../General/CollisionMaskEnums.h"

#include "glm/gtx/rotate_vector.hpp"

EnemyA::EnemyA() {
	addClassIdentifier(OBJECT_CLASS_ENEMY_A);

	setAttribute(ATTRIBUTE_COLLIDER_MASK_OWN,
		(int)getAttribute(ATTRIBUTE_COLLIDER_MASK_OWN) | (int)Collision_Masks::BULLET_ENEMY);
	
	setAttribute(ATTRIBUTE_BULLET_DAMAGE, 3);
	setAttribute(ATTRIBUTE_BULLET_ITIME, 1);
}
EnemyA::~EnemyA() {}


void EnemyA::getMovementDirection(float movementSlope[3]) const {
	
	float nod = getAttribute(ATTRIBUTE_SPATIAL_ROTATE_NOD);
	float turn = getAttribute(ATTRIBUTE_SPATIAL_ROTATE_TURN);
	
	glm::vec3 v = glm::rotate(glm::vec3{ 0.0f,0.0f,1.0f }, -glm::radians(nod), glm::vec3{ 1.0f,0.0f,0.0f });
	v = glm::rotate(v, -glm::radians(turn), glm::vec3{ 0.0f,1.0f,0.0f });
	
	movementSlope[0] = v.x;
	movementSlope[1] = v.y;
	movementSlope[2] = v.z;

}


void EnemyA::Bullet_onCollision() {
	queueDestroyObject(getIdentifier());
}
