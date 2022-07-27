#include "StageBorder.h"

#include "../../General/CollisionMaskEnums.h"

StageBorder::StageBorder() {
	addClassIdentifier(OBJECT_CLASS_STAGE_BORDER);
	createAttribute(ATTRIBUTE_STAGE_BORDER_SIDE, Attribute::types::INTEGER);

	setAttribute(ATTRIBUTE_COLLIDER_MASK_OWN, (int)Collision_Masks::BOUNDARY);
}
StageBorder::~StageBorder() {}