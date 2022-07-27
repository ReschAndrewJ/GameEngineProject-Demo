#include "TypeABullet.h"

#include "../SingleCallSound/SingleCallSound.h"

#include "../StageBorder/StageBorder.h"

TypeABullet::TypeABullet() {
	addClassIdentifier(OBJECT_CLASS_TYPE_A_BULLET);

	createAttribute(ATTRIBUTE_TYPE_A_BULLET_COLLISION_SOUND_FILE, Attribute::types::STRING);
	createAttribute(ATTRIBUTE_TYPE_A_BULLET_DIRECTION_X, Attribute::types::DOUBLE);
	createAttribute(ATTRIBUTE_TYPE_A_BULLET_DIRECTION_Y, Attribute::types::DOUBLE);
	createAttribute(ATTRIBUTE_TYPE_A_BULLET_DIRECTION_Z, Attribute::types::DOUBLE);
	createAttribute(ATTRIBUTE_TYPE_A_BULLET_SPEED, Attribute::types::DOUBLE);

	addProcessFunction(&process_func, 10);
}
TypeABullet::~TypeABullet() {}

void TypeABullet::process_func(Object* selfptr, float delta) {
	selfptr->setAttribute(ATTRIBUTE_SPATIAL_POSITION_X,
		(float)selfptr->getAttribute(ATTRIBUTE_SPATIAL_POSITION_X) +
		(float)selfptr->getAttribute(ATTRIBUTE_TYPE_A_BULLET_DIRECTION_X) *
		(float)selfptr->getAttribute(ATTRIBUTE_TYPE_A_BULLET_SPEED) * delta);

	selfptr->setAttribute(ATTRIBUTE_SPATIAL_POSITION_Y,
		(float)selfptr->getAttribute(ATTRIBUTE_SPATIAL_POSITION_Y) +
		(float)selfptr->getAttribute(ATTRIBUTE_TYPE_A_BULLET_DIRECTION_Y) * 
		(float)selfptr->getAttribute(ATTRIBUTE_TYPE_A_BULLET_SPEED) * delta);

	selfptr->setAttribute(ATTRIBUTE_SPATIAL_POSITION_Z,
		(float)selfptr->getAttribute(ATTRIBUTE_SPATIAL_POSITION_Z) +
		(float)selfptr->getAttribute(ATTRIBUTE_TYPE_A_BULLET_DIRECTION_Z) * 
		(float)selfptr->getAttribute(ATTRIBUTE_TYPE_A_BULLET_SPEED) * delta);

	auto colliders = dynamic_cast<TypeABullet*>(selfptr)->getCollidingObjects();
	for (const auto& collider : colliders) {
		if (selfptr->getObject(collider)->is_class(OBJECT_CLASS_STAGE_BORDER))
			selfptr->queueDestroyObject(selfptr->getIdentifier());
	}
}

void TypeABullet::Bullet_onCollision() {
	queueCreateObject("Resources/InstanceFiles/EmptyInsts.inst",
		"SingleCallSound", getParentIdentifier(), 
		{ {ATTRIBUTE_SOUND_FILE, getAttribute(ATTRIBUTE_TYPE_A_BULLET_COLLISION_SOUND_FILE)},
	{ATTRIBUTE_SOUND_VOLUME, 15} });
	queueDestroyObject(getIdentifier());
}