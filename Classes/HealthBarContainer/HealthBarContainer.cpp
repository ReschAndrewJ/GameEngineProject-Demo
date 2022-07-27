#include "HealthBarContainer.h"

#include "../HealthDisplayAbstract/HealthDisplayAbstract.h"

HealthBarContainer::HealthBarContainer() {
	addClassIdentifier(OBJECT_CLASS_HEALTH_BAR_CONTAINER);

	addProcessFunction(&process_func, 16);
}
HealthBarContainer::~HealthBarContainer() {}

void HealthBarContainer::process_func(Object* selfptr, float delta) {

	for (const auto& childId : selfptr->getChildrenIdentifiers()) {
		if (selfptr->getObject(childId)->is_class(OBJECT_CLASS_HEALTH_DISPLAY_ABSTRACT)) {

			if ((bool)selfptr->getObject(childId)->getAttribute(ATTRIBUTE_SPRITE_VISIBLE)) {
				selfptr->setAttribute(ATTRIBUTE_SPRITE_VISIBLE, true);
			}
			else {
				selfptr->setAttribute(ATTRIBUTE_SPRITE_VISIBLE, false);
			}
			break;
		}
	}

}