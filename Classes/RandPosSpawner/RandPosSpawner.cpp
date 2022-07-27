#include "RandPosSpawner.h"

RandPosSpawner::RandPosSpawner() {
	addClassIdentifier(OBJECT_CLASS_RAND_POS_SPAWNER);

	createAttribute(ATTRIBUTE_RAND_POS_SPAWNER_MIN_X, Attribute::types::DOUBLE);
	createAttribute(ATTRIBUTE_RAND_POS_SPAWNER_MIN_Y, Attribute::types::DOUBLE);
	createAttribute(ATTRIBUTE_RAND_POS_SPAWNER_MIN_Z, Attribute::types::DOUBLE);
	createAttribute(ATTRIBUTE_RAND_POS_SPAWNER_MAX_X, Attribute::types::DOUBLE);
	createAttribute(ATTRIBUTE_RAND_POS_SPAWNER_MAX_Y, Attribute::types::DOUBLE);
	createAttribute(ATTRIBUTE_RAND_POS_SPAWNER_MAX_Z, Attribute::types::DOUBLE);

	addProcessFunction(&process_func, 8);
}
RandPosSpawner::~RandPosSpawner() {}


void RandPosSpawner::process_func(Object* selfptr, float delta) {
	if (selfptr->getAttribute(ATTRIBUTE_TIMER_TIMEOUT)) {
		float posX = rand() % (int)((float)selfptr->getAttribute(ATTRIBUTE_RAND_POS_SPAWNER_MAX_X) -
			(float)selfptr->getAttribute(ATTRIBUTE_RAND_POS_SPAWNER_MIN_X)) + (float)selfptr->getAttribute(ATTRIBUTE_RAND_POS_SPAWNER_MIN_X);
		float posY = rand() % (int)((float)selfptr->getAttribute(ATTRIBUTE_RAND_POS_SPAWNER_MAX_Y) -
			(float)selfptr->getAttribute(ATTRIBUTE_RAND_POS_SPAWNER_MIN_Y)) + (float)selfptr->getAttribute(ATTRIBUTE_RAND_POS_SPAWNER_MIN_Y);
		float posZ = rand() % (int)((float)selfptr->getAttribute(ATTRIBUTE_RAND_POS_SPAWNER_MAX_Z) -
			(float)selfptr->getAttribute(ATTRIBUTE_RAND_POS_SPAWNER_MIN_Z)) + (float)selfptr->getAttribute(ATTRIBUTE_RAND_POS_SPAWNER_MIN_Z);

		selfptr->setAttribute(ATTRIBUTE_SPATIAL_POSITION_X, posX);
		selfptr->setAttribute(ATTRIBUTE_SPATIAL_POSITION_Y, posY);
		selfptr->setAttribute(ATTRIBUTE_SPATIAL_POSITION_Z, posZ);
	}
}