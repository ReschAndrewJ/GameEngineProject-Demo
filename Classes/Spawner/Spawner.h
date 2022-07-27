#ifndef OBJECT_SPAWNER
#define OBJECT_SPAWNER

// very similar to SpawnInfo
// spawns entities at a set rate until de-instanced

#include "../SpawnInfo/SpawnInfo.h"

const auto OBJECT_CLASS_SPAWNER = "Spawner";

// entity to spawn's information
const auto ATTRIBUTE_SPAWNER_ENTITY_FILEPATH = ATTRIBUTE_SPAWN_INFO_ENTITY_FILEPATH;
const auto ATTRIBUTE_SPAWNER_ENTITY_IDENTIFIER = ATTRIBUTE_SPAWN_INFO_ENTITY_IDENTIFIER;
// spawn delay
const auto ATTRIBUTE_SPAWNER_TIME_BETWEEN_SPAWNS = ATTRIBUTE_TIMER_LENGTH;
// spawns an entity on timerTimeout
const auto ATTRIBUTE_SPAWNER_TIME_OFFSET = ATTRIBUTE_TIMER_OFFSET;

const auto ATTRIBUTE_SPAWNER_SPAWN_COUNT = "SpawnerCount";
const auto ATTRIBUTE_SPAWNER_CURRENT_COUNT = "SpawnerCountCurrent";

class Spawner : public virtual Object_Spatial, public virtual SpawnInfo {
public:
	Spawner();
	virtual ~Spawner();

	static void afterCreation_func(Object*);
	static void process_func(Object*, float);
};


#endif // OBJECT_SPAWNER