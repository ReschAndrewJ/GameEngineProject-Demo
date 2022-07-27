#include "EnemyB.h"

#include "../Player/Player.h"
#include "../TypeABullet/TypeABullet.h"

EnemyB::EnemyB() {
	addClassIdentifier(OBJECT_CLASS_ENEMY_B);

	createAttribute(ATTRIBUTE_ENEMY_B_BULLET_FILEPATH, Attribute::types::STRING);
	createAttribute(ATTRIBUTE_ENEMY_B_BULLET_IDENTIFIER, Attribute::types::STRING);
	createAttribute(ATTRIBUTE_ENEMY_B_ON_COOLDOWN, Attribute::types::BOOLEAN);
	
	setAttribute(ATTRIBUTE_TIMER_LOOP, true);
	setAttribute(ATTRIBUTE_TIMER_RUNNING, true);

	addProcessFunction(&process_func, 10);
}
EnemyB::~EnemyB() {}


void EnemyB::process_func(Object* selfptr, float delta) {
	if ((bool)selfptr->getAttribute(ATTRIBUTE_TIMER_TIMEOUT)) selfptr->setAttribute(ATTRIBUTE_ENEMY_B_ON_COOLDOWN, false);
	if (!(bool)selfptr->getAttribute(ATTRIBUTE_ENEMY_B_ON_COOLDOWN)) {
		float playerPos[3]{};
		for (const auto& siblingId : selfptr->getObject(selfptr->getParentIdentifier())->getChildrenIdentifiers()) {
			if (selfptr->getObject(siblingId)->is_class(OBJECT_CLASS_PLAYER)) {
				playerPos[0] = selfptr->getObject(siblingId)->getAttribute(ATTRIBUTE_SPATIAL_POSITION_X);
				playerPos[1] = selfptr->getObject(siblingId)->getAttribute(ATTRIBUTE_SPATIAL_POSITION_Y);
				playerPos[2] = selfptr->getObject(siblingId)->getAttribute(ATTRIBUTE_SPATIAL_POSITION_Z);
				break;
			}
		}

		float ownPos[3] = { selfptr->getAttribute(ATTRIBUTE_SPATIAL_POSITION_X),
			selfptr->getAttribute(ATTRIBUTE_SPATIAL_POSITION_Y), selfptr->getAttribute(ATTRIBUTE_SPATIAL_POSITION_Z) };

		float diffs[3] = { playerPos[0] - ownPos[0], playerPos[1] - ownPos[1], playerPos[2] - ownPos[2] };

		if (diffs[2] < 0) return; // own shoot if the player is not behind the enemy

		float mag = sqrtf(diffs[0] * diffs[0] + diffs[1] * diffs[1] + diffs[2] * diffs[2]);
		float dir[3] = { diffs[0] / mag, diffs[1] / mag, diffs[2] / mag };
		
		selfptr->queueCreateObject(
			selfptr->getAttribute(ATTRIBUTE_ENEMY_B_BULLET_FILEPATH), selfptr->getAttribute(ATTRIBUTE_ENEMY_B_BULLET_IDENTIFIER),
			selfptr->getParentIdentifier(), {
				{ATTRIBUTE_SPATIAL_POSITION_X, selfptr->getAttribute(ATTRIBUTE_SPATIAL_POSITION_X)},
				{ATTRIBUTE_SPATIAL_POSITION_Y, selfptr->getAttribute(ATTRIBUTE_SPATIAL_POSITION_Y)},
				{ATTRIBUTE_SPATIAL_POSITION_Z, selfptr->getAttribute(ATTRIBUTE_SPATIAL_POSITION_Z)},
				{ATTRIBUTE_TYPE_A_BULLET_DIRECTION_X, dir[0]},
				{ATTRIBUTE_TYPE_A_BULLET_DIRECTION_Y, dir[1]},
				{ATTRIBUTE_TYPE_A_BULLET_DIRECTION_Z, dir[2]}
			}
		);
		selfptr->setAttribute(ATTRIBUTE_ENEMY_B_ON_COOLDOWN, true);
	}
}
