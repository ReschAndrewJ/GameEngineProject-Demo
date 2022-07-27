#include "Stage_Survival.h"



Stage_Survival::Stage_Survival() {
	addClassIdentifier(OBJECT_CLASS_STAGE_SURVIVAL);

	createAttribute(ATTRIBUTE_STAGE_SURVIVAL_END_TIME, Attribute::types::DOUBLE);
}
Stage_Survival::~Stage_Survival() {}


bool Stage_Survival::isStageComplete() const {
	return (float)getAttribute(ATTRIBUTE_STAGE_TIME_ELAPSED)
		> (float)getAttribute(ATTRIBUTE_STAGE_SURVIVAL_END_TIME);
}