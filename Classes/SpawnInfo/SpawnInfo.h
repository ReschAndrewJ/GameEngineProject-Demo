#ifndef OBJECT_SPAWN_INFO
#define OBJECT_SPAWN_INFO

// By setting a stage instance to have several spawn info instances,
// an instance file can be used as a sort of "beatmap" for the stage

#include "../../_GameEngineSrc/Objects/Spatial/Object_Spatial.h"
#include "../Timer/Timer.h"

const auto OBJECT_CLASS_SPAWN_INFO = "SpawnInfo";

// inst filepath
const auto ATTRIBUTE_SPAWN_INFO_ENTITY_FILEPATH = "SpawnInfoEntityFilepath";
// instance identifier
const auto ATTRIBUTE_SPAWN_INFO_ENTITY_IDENTIFIER = "SpawnInfoEntityIdentifier";
// at what point during the stage the entity should spawn
const auto ATTRIBUTE_SPAWN_INFO_SPAWN_TIME = ATTRIBUTE_TIMER_LENGTH;
const auto ATTRIBUTE_SPAWN_INFO_CURRENT_TIME = ATTRIBUTE_TIMER_OFFSET;

class SpawnInfo : public virtual Object_Spatial, public virtual Timer {
public:
	SpawnInfo();
	virtual ~SpawnInfo();

	static void processFunc(Object*, float);
};

#endif OBJECT_SPAWN_INFO