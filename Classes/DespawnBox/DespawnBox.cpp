#include "DespawnBox.h"

#include "../../_GameEngineSrc/Objects/Collision/Object_Collision.h"
#include "../Boss/Boss.h"

DespawnBox::DespawnBox() {
	addClassIdentifier(OBJECT_CLASS_DESPAWN_BOX);
	addProcessFunction(&process_func, 16);
}
DespawnBox::~DespawnBox() {}


void DespawnBox::process_func(Object* selfptr, float delta) {
	for (const auto& child : selfptr->getChildrenIdentifiers()) {
		if (!selfptr->getObject(child)->is_class(OBJECT_CLASS_COLLISION)) return;
		for (const auto& collider :
			dynamic_cast<Object_Collision*>(selfptr->getObject(child))->getCollidingObjects()) {
			if (!selfptr->getObject(collider)->is_class(OBJECT_CLASS_BOSS))
				selfptr->queueDestroyObject(collider); 
		}
	}
}
