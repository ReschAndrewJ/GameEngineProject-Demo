#ifndef RAND_POS_SPAWNER
#define RAND_POS_SPAWNER

#include "../Spawner/Spawner.h"

const auto OBJECT_CLASS_RAND_POS_SPAWNER = "RandPosSpawner";

const auto ATTRIBUTE_RAND_POS_SPAWNER_MIN_X = "RandPosSpawnerMinX";
const auto ATTRIBUTE_RAND_POS_SPAWNER_MIN_Y = "RandPosSpawnerMinY";
const auto ATTRIBUTE_RAND_POS_SPAWNER_MIN_Z = "RandPosSpawnerMinZ";

const auto ATTRIBUTE_RAND_POS_SPAWNER_MAX_X = "RandPosSpawnerMaxX";
const auto ATTRIBUTE_RAND_POS_SPAWNER_MAX_Y = "RandPosSpawnerMaxY";
const auto ATTRIBUTE_RAND_POS_SPAWNER_MAX_Z = "RandPosSpawnerMaxZ";

class RandPosSpawner : public virtual Spawner {
public:
	RandPosSpawner();
	virtual ~RandPosSpawner();

	static void process_func(Object*, float);
};


#endif