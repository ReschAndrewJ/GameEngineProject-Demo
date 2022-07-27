#include "Stage_Boss.h"

#include "../Boss/Boss.h"

Stage_Boss::Stage_Boss() {
	addClassIdentifier(OBJECT_CLASS_STAGE_BOSS);
}
Stage_Boss::~Stage_Boss() {}

bool Stage_Boss::isStageComplete() const {
	for (const auto& childId : getChildrenIdentifiers()) {
		if (getObject(childId)->is_class(OBJECT_CLASS_BOSS)) return false;
	}
	return true;
}