#include "EnemyC.h"

#include "../Player/Player.h"
#include "../TypeABullet/TypeABullet.h"

EnemyC::EnemyC() {
	addClassIdentifier(OBJECT_CLASS_ENEMY_C);

	createAttribute(ATTRIBUTE_ENEMY_C_BULLET_FILEPATH, Attribute::types::STRING);
	createAttribute(ATTRIBUTE_ENEMY_C_BULLET_IDENTIFIER, Attribute::types::STRING);
	createAttribute(ATTRIBUTE_ENEMY_C_ON_COOLDOWN, Attribute::types::BOOLEAN);
	
	createAttribute(ATTRIBUTE_ENEMY_C_BULLET_DIRECTION_X, Attribute::types::DOUBLE);
	createAttribute(ATTRIBUTE_ENEMY_C_BULLET_DIRECTION_Y, Attribute::types::DOUBLE);
	createAttribute(ATTRIBUTE_ENEMY_C_BULLET_DIRECTION_Z, Attribute::types::DOUBLE);
	setAttribute(ATTRIBUTE_ENEMY_C_BULLET_DIRECTION_Z, 1);

	setAttribute(ATTRIBUTE_TIMER_LOOP, true);
	setAttribute(ATTRIBUTE_TIMER_RUNNING, true);

	addProcessFunction(&process_func, 10);
}
EnemyC::~EnemyC() {}


void EnemyC::process_func(Object* selfptr, float delta) {
	if ((bool)selfptr->getAttribute(ATTRIBUTE_TIMER_TIMEOUT)) selfptr->setAttribute(ATTRIBUTE_ENEMY_C_ON_COOLDOWN, false);
	if (!(bool)selfptr->getAttribute(ATTRIBUTE_ENEMY_C_ON_COOLDOWN)) {
		
		float dir[3] = { (float)selfptr->getAttribute(ATTRIBUTE_ENEMY_C_BULLET_DIRECTION_X),
		(float)selfptr->getAttribute(ATTRIBUTE_ENEMY_C_BULLET_DIRECTION_Y),
		(float)selfptr->getAttribute(ATTRIBUTE_ENEMY_C_BULLET_DIRECTION_Z) };

		selfptr->queueCreateObject(
			selfptr->getAttribute(ATTRIBUTE_ENEMY_C_BULLET_FILEPATH), selfptr->getAttribute(ATTRIBUTE_ENEMY_C_BULLET_IDENTIFIER),
			selfptr->getParentIdentifier(), {
				{ATTRIBUTE_SPATIAL_POSITION_X, selfptr->getAttribute(ATTRIBUTE_SPATIAL_POSITION_X)},
				{ATTRIBUTE_SPATIAL_POSITION_Y, selfptr->getAttribute(ATTRIBUTE_SPATIAL_POSITION_Y)},
				{ATTRIBUTE_SPATIAL_POSITION_Z, selfptr->getAttribute(ATTRIBUTE_SPATIAL_POSITION_Z)},
				{ATTRIBUTE_TYPE_A_BULLET_DIRECTION_X, dir[0]},
				{ATTRIBUTE_TYPE_A_BULLET_DIRECTION_Y, dir[1]},
				{ATTRIBUTE_TYPE_A_BULLET_DIRECTION_Z, dir[2]}
			}
		);
		selfptr->setAttribute(ATTRIBUTE_ENEMY_C_ON_COOLDOWN, true);
	}
}
