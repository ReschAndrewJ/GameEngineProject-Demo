#include "Boss.h"
#include "../Stage_Boss/Stage_Boss.h"

Boss::Boss() {
	addClassIdentifier(OBJECT_CLASS_BOSS);

	createAttribute(ATTRIBUTE_BOSS_MIN_X, Attribute::types::DOUBLE);
	createAttribute(ATTRIBUTE_BOSS_MAX_X, Attribute::types::DOUBLE);
	createAttribute(ATTRIBUTE_BOSS_MIN_Y, Attribute::types::DOUBLE);
	createAttribute(ATTRIBUTE_BOSS_MAX_Y, Attribute::types::DOUBLE);
	createAttribute(ATTRIBUTE_BOSS_MIN_Z, Attribute::types::DOUBLE);
	createAttribute(ATTRIBUTE_BOSS_MAX_Z, Attribute::types::DOUBLE);

	createAttribute(ATTRIBUTE_BOSS_BASE_SPEED, Attribute::types::DOUBLE);

	addAfterCreationFunction(&afterCreation_func);
	addProcessFunction(&process_func, 10);
}
Boss::~Boss() {}

void Boss::afterCreation_func(Object* selfptr) {
	dynamic_cast<Boss*>(selfptr)->randomizeTargetPos();
}

void Boss::process_func(Object* selfptr, float delta) {
	if (selfptr->getObject(selfptr->getParentIdentifier())->is_class(OBJECT_CLASS_STAGE_BOSS) &&
		!(bool)selfptr->getObject(selfptr->getParentIdentifier())->getAttribute(ATTRIBUTE_STAGE_TIME_COUNTING)) return;

	selfptr->setAttribute(ATTRIBUTE_LIVE_ENTITY_MOVE_SPEED,
		(float)selfptr->getAttribute(ATTRIBUTE_BOSS_BASE_SPEED) * (1 +
			(float)selfptr->getAttribute(ATTRIBUTE_LIVE_ENTITY_CURRENT_HEALTH)
			/ (float)selfptr->getAttribute(ATTRIBUTE_LIVE_ENTITY_MAX_HEALTH))
	);

	Boss* self = dynamic_cast<Boss*>(selfptr);
	if (abs((float)self->getAttribute(ATTRIBUTE_SPATIAL_POSITION_X) - self->targetPos[0])
		< delta * (float)self->getAttribute(ATTRIBUTE_LIVE_ENTITY_MOVE_SPEED) &&
		abs((float)self->getAttribute(ATTRIBUTE_SPATIAL_POSITION_Y) - self->targetPos[1])
		< delta * (float)self->getAttribute(ATTRIBUTE_LIVE_ENTITY_MOVE_SPEED) &&
		abs((float)self->getAttribute(ATTRIBUTE_SPATIAL_POSITION_Z) - self->targetPos[2])
		< delta * (float)self->getAttribute(ATTRIBUTE_LIVE_ENTITY_MOVE_SPEED)) {

		self->randomizeTargetPos();
	}
}



void Boss::getMovementDirection(float movementSlope[3]) const {
	if (getObject(getParentIdentifier())->is_class(OBJECT_CLASS_STAGE_BOSS) &&
		!(bool)getObject(getParentIdentifier())->getAttribute(ATTRIBUTE_STAGE_TIME_COUNTING)) return;

	float posX = getAttribute(ATTRIBUTE_SPATIAL_POSITION_X);
	float posY = getAttribute(ATTRIBUTE_SPATIAL_POSITION_Y);
	float posZ = getAttribute(ATTRIBUTE_SPATIAL_POSITION_Z);
	
	float xDiff = targetPos[0] - posX;
	float yDiff = targetPos[1] - posY;
	float zDiff = targetPos[2] - posZ;

	float len = sqrtf(xDiff * xDiff + yDiff * yDiff + zDiff * zDiff);

	float slopeX = xDiff / len;
	float slopeY = yDiff / len;
	float slopeZ = zDiff / len;

	movementSlope[0] = slopeX;
	movementSlope[1] = slopeY;
	movementSlope[2] = slopeZ;

}


void Boss::Bullet_onCollision() {}


void Boss::randomizeTargetPos() {
	targetPos[0] = (rand() % ((int)getAttribute(ATTRIBUTE_BOSS_MAX_X) - (int)getAttribute(ATTRIBUTE_BOSS_MIN_X)))
		+ (float)getAttribute(ATTRIBUTE_BOSS_MIN_X);
	targetPos[1] = (rand() % ((int)getAttribute(ATTRIBUTE_BOSS_MAX_Y) - (int)getAttribute(ATTRIBUTE_BOSS_MIN_Y)))
		+ (float)getAttribute(ATTRIBUTE_BOSS_MIN_Y);
	targetPos[2] = (rand() % ((int)getAttribute(ATTRIBUTE_BOSS_MAX_Z) - (int)getAttribute(ATTRIBUTE_BOSS_MIN_Z)))
		+ (float)getAttribute(ATTRIBUTE_BOSS_MIN_Z);
}