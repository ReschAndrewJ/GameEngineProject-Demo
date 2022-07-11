#ifndef OBJECT_STAGE_BORDER
#define OBJECT_STAGE_BORDER

#include "../../_GameEngineSrc/Objects/Collision/Object_Collision.h"
#include "../../_GameEngineSrc/Objects/AnimatedSprite/Object_AnimatedSprite.h"

const auto OBJECT_CLASS_STAGE_BORDER = "StageBorder";

class StageBorder : public virtual Object_Collision, public virtual Object_AnimatedSprite {
public:
	StageBorder();
	virtual ~StageBorder();
};


#endif // OBJECT_STAGE_BORDER