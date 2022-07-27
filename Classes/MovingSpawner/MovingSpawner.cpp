#include "MovingSpawner.h"

MovingSpawner::MovingSpawner() {
	addClassIdentifier(OBJECT_CLASS_MOVING_SPAWNER);

	createAttribute(ATTRIBUTE_MOVING_SPAWNER_MOVE_X, Attribute::types::DOUBLE);
	createAttribute(ATTRIBUTE_MOVING_SPAWNER_MOVE_Y, Attribute::types::DOUBLE);
	createAttribute(ATTRIBUTE_MOVING_SPAWNER_MOVE_Z, Attribute::types::DOUBLE);

	addProcessFunction(&process_func, 10);
}
MovingSpawner::~MovingSpawner() {}


void MovingSpawner::process_func(Object* selfptr, float delta) {
	selfptr->setAttribute(ATTRIBUTE_SPATIAL_POSITION_X,
		(float)selfptr->getAttribute(ATTRIBUTE_SPATIAL_POSITION_X) +
		(float)selfptr->getAttribute(ATTRIBUTE_MOVING_SPAWNER_MOVE_X) * delta);
	selfptr->setAttribute(ATTRIBUTE_SPATIAL_POSITION_Y,
		(float)selfptr->getAttribute(ATTRIBUTE_SPATIAL_POSITION_Y) +
		(float)selfptr->getAttribute(ATTRIBUTE_MOVING_SPAWNER_MOVE_Y) * delta);
	selfptr->setAttribute(ATTRIBUTE_SPATIAL_POSITION_Z,
		(float)selfptr->getAttribute(ATTRIBUTE_SPATIAL_POSITION_Z) +
		(float)selfptr->getAttribute(ATTRIBUTE_MOVING_SPAWNER_MOVE_Z) * delta);
}
