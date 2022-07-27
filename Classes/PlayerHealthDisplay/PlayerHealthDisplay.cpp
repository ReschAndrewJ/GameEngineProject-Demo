#include "PlayerHealthDisplay.h"

#include "../Player/Player.h"

PlayerHealthDisplay::PlayerHealthDisplay() {
	addClassIdentifier(OBJECT_CLASS_PLAYER_HEALTH_DISPLAY);
	addRequestedPointer(PTR_IDENTIFIER::OBJ_CONTAINER_PTR, &objectsContainerPtr);

	addProcessFunction(&process_func, 15);
}
PlayerHealthDisplay::~PlayerHealthDisplay() {}


void PlayerHealthDisplay::process_func(Object* selfptr, float delta) {
	// verify correctness of playerId helper variable
	PlayerHealthDisplay* self = dynamic_cast<PlayerHealthDisplay*>(selfptr);
	if (self->getObject(self->playerId) == nullptr) {
		for (const auto& obj : *(self->objectsContainerPtr)) 
			if (obj.second->is_class(OBJECT_CLASS_PLAYER)) {
				self->playerId = obj.first;
				break;
		}
		if (self->getObject(self->playerId) == nullptr) return;
	}

	// collect player object's health information
	float healthPercent =
		(float)self->getObject(self->playerId)->
			getAttribute(ATTRIBUTE_LIVE_ENTITY_CURRENT_HEALTH)
		/ (float)self->getObject(self->playerId)->
			getAttribute(ATTRIBUTE_LIVE_ENTITY_MAX_HEALTH);
	float barCenteredPos = healthPercent / 2;

	self->setAttribute(ATTRIBUTE_SPATIAL_POSITION_X, barCenteredPos - 0.5);
	self->setAttribute(ATTRIBUTE_SPATIAL_SCALE_X, healthPercent);

}