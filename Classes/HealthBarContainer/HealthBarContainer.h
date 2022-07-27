#ifndef HEALTH_BAR_CONTAINER
#define HEALTH_BAR_CONTAINER

#include "../../_GameEngineSrc/Objects/Sprite/Object_Sprite.h"

const auto OBJECT_CLASS_HEALTH_BAR_CONTAINER = "HealthBarContainer";

class HealthBarContainer : public virtual Object_Sprite {
public:
	HealthBarContainer();
	virtual ~HealthBarContainer();

	static void process_func(Object*, float);
};


#endif