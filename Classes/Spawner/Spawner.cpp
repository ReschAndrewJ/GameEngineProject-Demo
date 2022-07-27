#include "Spawner.h"


Spawner::Spawner() {
	addClassIdentifier(OBJECT_CLASS_SPAWNER);

	createAttribute(ATTRIBUTE_SPAWNER_SPAWN_COUNT, Attribute::types::INTEGER);
	createAttribute(ATTRIBUTE_SPAWNER_CURRENT_COUNT, Attribute::types::INTEGER);

	setAttribute(ATTRIBUTE_TIMER_LOOP, true);
	setAttribute(ATTRIBUTE_TIMER_RUNNING, true);
	
	addAfterCreationFunction(&afterCreation_func);
	addProcessFunction(&process_func, 10);
}
Spawner::~Spawner() {}

void Spawner::afterCreation_func(Object* selfptr) {
	selfptr->setAttribute(
		ATTRIBUTE_SPAWNER_CURRENT_COUNT, (int)selfptr->getAttribute(ATTRIBUTE_SPAWNER_CURRENT_COUNT) + 1
	);
	selfptr->queueCreateObject(selfptr->getAttribute(ATTRIBUTE_SPAWN_INFO_ENTITY_FILEPATH),
		selfptr->getAttribute(ATTRIBUTE_SPAWN_INFO_ENTITY_IDENTIFIER), selfptr->getParentIdentifier(), {
			{ATTRIBUTE_SPATIAL_POSITION_X, selfptr->getAttribute(ATTRIBUTE_SPATIAL_POSITION_X)},
			{ATTRIBUTE_SPATIAL_POSITION_Y, selfptr->getAttribute(ATTRIBUTE_SPATIAL_POSITION_Y)},
			{ATTRIBUTE_SPATIAL_POSITION_Z, selfptr->getAttribute(ATTRIBUTE_SPATIAL_POSITION_Z)},
			{ATTRIBUTE_SPATIAL_ROTATE_NOD, selfptr->getAttribute(ATTRIBUTE_SPATIAL_ROTATE_NOD)},
			{ATTRIBUTE_SPATIAL_ROTATE_TURN, selfptr->getAttribute(ATTRIBUTE_SPATIAL_ROTATE_TURN)},
			{ATTRIBUTE_SPATIAL_ROTATE_TILT, selfptr->getAttribute(ATTRIBUTE_SPATIAL_ROTATE_TILT)},	
		});
}

void Spawner::process_func(Object* selfptr, float delta) {
	
	if (selfptr->getAttribute(ATTRIBUTE_TIMER_TIMEOUT)) selfptr->setAttribute(
		ATTRIBUTE_SPAWNER_CURRENT_COUNT, (int)selfptr->getAttribute(ATTRIBUTE_SPAWNER_CURRENT_COUNT) + 1
	);
	if ((int)selfptr->getAttribute(ATTRIBUTE_SPAWNER_CURRENT_COUNT) >=
		(int)selfptr->getAttribute(ATTRIBUTE_SPAWNER_SPAWN_COUNT) 
		&& (int)selfptr->getAttribute(ATTRIBUTE_SPAWNER_SPAWN_COUNT) != -1)
		selfptr->queueDestroyObject(selfptr->getIdentifier());
			
}