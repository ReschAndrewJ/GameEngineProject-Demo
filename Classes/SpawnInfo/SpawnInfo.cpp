#include "SpawnInfo.h"

SpawnInfo::SpawnInfo() {
	addClassIdentifier(OBJECT_CLASS_SPAWN_INFO);

	createAttribute(ATTRIBUTE_SPAWN_INFO_ENTITY_FILEPATH, Attribute::types::STRING);
	createAttribute(ATTRIBUTE_SPAWN_INFO_ENTITY_IDENTIFIER, Attribute::types::STRING);
	
	addProcessFunction(&processFunc, 10);
}
SpawnInfo::~SpawnInfo() {}


void SpawnInfo::processFunc(Object* selfptr, float delta) {
	if ((bool)selfptr->getAttribute(ATTRIBUTE_TIMER_TIMEOUT)) {
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
}