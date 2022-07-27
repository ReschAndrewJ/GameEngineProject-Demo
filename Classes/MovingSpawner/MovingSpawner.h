#ifndef MOVING_SPAWNER
#define MOVING_SPAWNER

#include "../Spawner/Spawner.h"

const auto OBJECT_CLASS_MOVING_SPAWNER = "MovingSpawner";

const auto ATTRIBUTE_MOVING_SPAWNER_MOVE_X = "MovingSpawnerMoveX";
const auto ATTRIBUTE_MOVING_SPAWNER_MOVE_Y= "MovingSpawnerMoveY";
const auto ATTRIBUTE_MOVING_SPAWNER_MOVE_Z = "MovingSpawnerMoveZ";

class MovingSpawner : public virtual Spawner {
public:
	MovingSpawner();
	virtual ~MovingSpawner();

	static void process_func(Object*, float);
};


#endif