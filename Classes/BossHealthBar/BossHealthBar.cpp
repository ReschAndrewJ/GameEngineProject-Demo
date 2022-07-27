#include "BossHealthBar.h"

#include "../Boss/Boss.h"



BossHealthBar::BossHealthBar() {
	addClassIdentifier(OBJECT_CLASS_BOSS_HEALTH_BAR);
	addRequestedPointer(PTR_IDENTIFIER::OBJ_CONTAINER_PTR, &objectsContainerPtr);

	addProcessFunction(&process_func, 15);
}
BossHealthBar::~BossHealthBar() {}



void BossHealthBar::process_func(Object* selfptr, float delta) {
	// verify correctness of bossId helper variable
	BossHealthBar* self = dynamic_cast<BossHealthBar*>(selfptr);
	if (self->getObject(self->bossId) == nullptr) {
		for (const auto& obj : *(self->objectsContainerPtr))
			if (obj.second->is_class(OBJECT_CLASS_BOSS)) {
				self->bossId = obj.first;
				self->setAttribute(ATTRIBUTE_SPRITE_VISIBLE, true);
				break;
			}
		if (self->getObject(self->bossId) == nullptr) {
				self->setAttribute(ATTRIBUTE_SPRITE_VISIBLE, false);
				return;
		}
	}

	// collect boss object's health information
	float healthPercent =
		(float)self->getObject(self->bossId)->
		getAttribute(ATTRIBUTE_LIVE_ENTITY_CURRENT_HEALTH)
		/ (float)self->getObject(self->bossId)->
		getAttribute(ATTRIBUTE_LIVE_ENTITY_MAX_HEALTH);
	float barCenteredPos = -healthPercent / 2;

	self->setAttribute(ATTRIBUTE_SPATIAL_POSITION_X, barCenteredPos + 0.5);
	self->setAttribute(ATTRIBUTE_SPATIAL_SCALE_X, healthPercent);

}