#include "Spawner.h"


Spawner::Spawner() {
	addClassIdentifier(OBJECT_CLASS_SPAWNER);

	setAttribute(ATTRIBUTE_TIMER_LOOP, true);
}
Spawner::~Spawner() {}


