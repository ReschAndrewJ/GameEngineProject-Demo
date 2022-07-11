#ifndef OBJECT_STAGE
#define OBJECT_STAGE

// the stage contains the ground, walls, and sky box, as well as the player
// and all of the enemies, bullets, and spawners

// SELF-NOTE: the side of the box being viewed from will likely need to be transparent for the camera

#include "../../_GameEngineSrc/Objects/Spatial/Object_Spatial.h"

const auto OBJECT_CLASS_STAGE = "Stage";

// is set to true when the stage is completed
const auto ATTRIBUTE_STAGE_COMPLETE = "StageComplete";
const auto ATTRIBUTE_STAGE_NEXT_FILEPATH = "StageNextFilepath";
const auto ATTRIBUTE_STAGE_NEXT_IDENTIFIER = "StageNextIdentifier";


// the direction from which the stage is viewed
const auto ATTRIBUTE_STAGE_VIEW = "StageView";


// the distance from the origin that the center of the stage should be,
// or rather, the distance from the center of the stage that the camera should be 

const auto ATTRIBUTE_STAGE_TOP_DISTANCE = "StageTopDistance";
const auto ATTRIBUTE_STAGE_BACK_DISTANCE = "StageBackDistance";
const auto ATTRIBUTE_STAGE_SIDE_DISTANCE = "StageSideDistance";

const auto ATTRIBUTE_STAGE_ROTATION_SPEED = "StageRotSpeed";
const auto ATTRIBUTE_STAGE_DISTANCE_SPEED = "StageDistSpeed";


class Stage : public virtual Object_Spatial {
public:
	Stage();
	virtual ~Stage();

	static void afterCreationFunc(Object*);
	static void processFunc(Object*, float);

protected:
	// defines the conditions under which the stage is considered completed
	virtual bool isStageComplete() const = 0;
};


#endif // OBJECT_STAGE