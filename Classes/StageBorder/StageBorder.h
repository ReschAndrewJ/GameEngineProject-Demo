#ifndef OBJECT_STAGE_BORDER
#define OBJECT_STAGE_BORDER

#include "../../_GameEngineSrc/Objects/Collision/Object_Collision.h"
#include "../../_GameEngineSrc/Objects/AnimatedSprite/Object_AnimatedSprite.h"

const auto OBJECT_CLASS_STAGE_BORDER = "StageBorder";

const auto STAGE_BORDER_TOP = 1;
const auto STAGE_BORDER_FRONT = 2;
const auto STAGE_BORDER_RIGHT = 3;

const auto ATTRIBUTE_STAGE_BORDER_SIDE = "StageBorderSide";

class StageBorder : public virtual Object_Collision, public virtual Object_AnimatedSprite {
public:
	StageBorder();
	virtual ~StageBorder();
};


#endif // OBJECT_STAGE_BORDER