#include "LiveEntity.h"

#include "../../General/collisionMaskEnums.h"
#include "../Timer/Timer.h"
#include "../Bullet/Bullet.h"


LiveEntity::LiveEntity() {
	addClassIdentifier(OBJECT_CLASS_LIVE_ENTITY);

	createAttribute(ATTRIBUTE_LIVE_ENTITY_MAX_HEALTH, Attribute::types::INTEGER);
	createAttribute(ATTRIBUTE_LIVE_ENTITY_CURRENT_HEALTH, Attribute::types::INTEGER);
	createAttribute(ATTRIBUTE_LIVE_ENTITY_MOVE_SPEED, Attribute::types::DOUBLE);
	setAttribute(ATTRIBUTE_LIVE_ENTITY_MAX_HEALTH, 1);
	setAttribute(ATTRIBUTE_LIVE_ENTITY_MOVE_SPEED, 100);

	createAttribute(ATTRIBUTE_LIVE_ENTITY_IFRAME_MASK, Attribute::types::INTEGER);

	addAfterCreationFunction(&afterCreationFunc);
	addProcessFunction(&processFunc, 5);
}
LiveEntity::~LiveEntity() {}

void LiveEntity::onDeath() { queueDestroyObject(getIdentifier()); }
void LiveEntity::onDamage() {}

void LiveEntity::afterCreationFunc(Object* selfptr) {
	if ((bool)selfptr->getAttribute(ATTRIBUTE_LIVE_ENTITY_CURRENT_HEALTH) == 0) {
		selfptr->setAttribute(ATTRIBUTE_LIVE_ENTITY_CURRENT_HEALTH, 
			selfptr->getAttribute(ATTRIBUTE_LIVE_ENTITY_MAX_HEALTH));
	}

	dynamic_cast<LiveEntity*>(selfptr)->helperCollisionMask = selfptr->getAttribute(ATTRIBUTE_COLLIDER_MASK_TARGET);

	selfptr->queueCreateObject("Resources/InstanceFiles/EmptyInsts.inst", "emptyTimer", selfptr->getIdentifier(), {});
}


void LiveEntity::processFunc(Object* selfptr, float delta) {
	LiveEntity* self = dynamic_cast<LiveEntity*>(selfptr);

	// setup helper identifier for the iframe timer if not setup already
	if (self->iFrameTimerIdentifier == TIMER_NOT_FOUND) {
		for (const std::string& childStr : self->getChildrenIdentifiers()) {
			if (childStr.find("emptyTimer") != std::string::npos) {
				self->iFrameTimerIdentifier = childStr;
				break;
			}
		}
	}

	// handle iframe timeout
	Object* iframeTimerPtr = (self->iFrameTimerIdentifier == TIMER_NOT_FOUND) 
		? nullptr : self->getObject(self->iFrameTimerIdentifier);
	if (iframeTimerPtr != nullptr
		&& (bool)iframeTimerPtr->getAttribute(ATTRIBUTE_TIMER_TIMEOUT)) {
		self->setAttribute(ATTRIBUTE_COLLIDER_MASK_TARGET, self->helperCollisionMask);
	}

	// get movement
	float dir[3]{};
	self->getMovementDirection(dir);
	std::vector<std::string> collisions = self->move(
		dir[0], dir[1], dir[2], delta,
		self->getAttribute(ATTRIBUTE_LIVE_ENTITY_MOVE_SPEED)
	);

	// check collisions
	if (collisions.size() != 0) {
		long long currHealth = self->getAttribute(ATTRIBUTE_LIVE_ENTITY_CURRENT_HEALTH);
		double iTime = 0;

		for (std::string& collider : collisions) {
			Object_Collision* colliderPtr = dynamic_cast<Object_Collision*>(self->getObject(collider));
			if (colliderPtr->is_class(OBJECT_CLASS_BULLET)) {
				Bullet* bulletPtr = dynamic_cast<Bullet*>(colliderPtr);
				currHealth -= (long long)bulletPtr->getAttribute(ATTRIBUTE_BULLET_DAMAGE);

				if ((double)bulletPtr->getAttribute(ATTRIBUTE_BULLET_ITIME) > iTime) {
					iTime = bulletPtr->getAttribute(ATTRIBUTE_BULLET_ITIME);
				}
				bulletPtr->Bullet_onCollision();
				self->onDamage();
			}

		}
		// start iframe timer
		if (iframeTimerPtr != nullptr) {
			iframeTimerPtr->setAttribute(ATTRIBUTE_TIMER_LENGTH, iTime);
			dynamic_cast<Timer*>(iframeTimerPtr)->startTimer();
			self->setAttribute(ATTRIBUTE_COLLIDER_MASK_TARGET, self->getAttribute(ATTRIBUTE_LIVE_ENTITY_IFRAME_MASK));
		}
		self->setAttribute(ATTRIBUTE_LIVE_ENTITY_CURRENT_HEALTH, currHealth);

		// handle death
		if (currHealth <= 0) self->onDeath();

	}


}