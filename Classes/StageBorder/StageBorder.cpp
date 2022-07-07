#include "StageBorder.h"

#include "../../General/CollisionMaskEnums.h"

StageBorder::StageBorder() {
	addClassIdentifier(OBJECT_CLASS_STAGE_BORDER);

	setAttribute(ATTRIBUTE_COLLIDER_MASK_OWN, (int)Collision_Masks::BOUNDARY);
}
StageBorder::~StageBorder() {}