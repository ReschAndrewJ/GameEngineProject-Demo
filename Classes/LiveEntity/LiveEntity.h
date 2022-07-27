#ifndef OBJECT_LIVE_ENTITY
#define OBJECT_LIVE_ENTITY

#include "../../_GameEngineSrc/Objects/ActiveCollision/Object_ActiveCollision.h"

const auto OBJECT_CLASS_LIVE_ENTITY = "LiveEntity";

// the maximum number of health points of the object
const auto ATTRIBUTE_LIVE_ENTITY_MAX_HEALTH = "LiveEntityMaxHealth";
// the current number of health points of the object
// set to a non-zero value before instancing to spawn the object at a value other than MaxHealth
const auto ATTRIBUTE_LIVE_ENTITY_CURRENT_HEALTH = "LiveEntityCurrentHealth";
// the speed value that the getMovementDirection function's return vector is multiplied by to control movement
const auto ATTRIBUTE_LIVE_ENTITY_MOVE_SPEED = "LiveEntitySpeed";

// the collision mask used during entity iframes
const auto ATTRIBUTE_LIVE_ENTITY_IFRAME_MASK = "LiveEntityIFrameMask";

// helper constant
const auto TIMER_NOT_FOUND = "NOT_FOUND";

class LiveEntity : public virtual Object_ActiveCollision {
public:
	LiveEntity();
	virtual ~LiveEntity();

	static void afterCreationFunc(Object*);
	static void processFunc(Object*, float);

protected:
	virtual void getMovementDirection(float XYZ[3]) const = 0;
	virtual void onDeath();

	virtual void onDamage();

private:
	// holds onto the primary collision mask while the object is undergoing iframes
	long long helperCollisionMask = 0;

	std::string iFrameTimerIdentifier = TIMER_NOT_FOUND;
};


#endif // OBJECT_LIVE_ENTITY