#ifndef OBJECT_STAGE
#define OBJECT_STAGE

// the stage contains the ground, walls, and sky box, as well as the player
// and all of the enemies, bullets, and spawners

// SELF-NOTE: the side of the box being viewed from will likely need to be transparent for the camera

#include "GameEngineLib/Objects/Spatial/Object_Spatial.h"

const auto OBJECT_CLASS_STAGE = "Stage";

// is set to true when the stage is completed
const auto ATTRIBUTE_STAGE_COMPLETE = "StageComplete";
const auto ATTRIBUTE_STAGE_NEXT_FILEPATH = "StageNextFilepath";
const auto ATTRIBUTE_STAGE_NEXT_IDENTIFIER = "StageNextIdentifier";

// the direction from which the stage is viewed
const auto ATTRIBUTE_STAGE_VIEW = "StageView";

class Stage : public virtual Object_Spatial {
public:
	Stage();
	virtual ~Stage();


protected:
	// defines the conditions under which the stage is considered completed
	virtual bool isStageComplete() const = 0;
};


#endif // OBJECT_STAGE