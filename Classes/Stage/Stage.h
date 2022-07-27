#ifndef OBJECT_STAGE
#define OBJECT_STAGE

// the stage contains the ground, walls, and sky box, as well as the player
// and all of the enemies, bullets, and spawners

// SELF-NOTE: the side of the box being viewed from will likely need to be transparent for the camera
	// DONE

#include "../../_GameEngineSrc/Objects/Spatial/Object_Spatial.h"
#include "../../_GameEngineSrc/Objects/SoundOutput/Object_SoundOutput.h"

const auto OBJECT_CLASS_STAGE = "Stage";

// is set to true when the stage is completed
const auto ATTRIBUTE_STAGE_COMPLETE = "StageComplete";
const auto ATTRIBUTE_STAGE_NEXT_FILEPATH = "StageNextFilepath";
const auto ATTRIBUTE_STAGE_NEXT_IDENTIFIER = "StageNextIdentifier";
// true for smooth transition, false for hard transition
const auto ATTRIBUTE_STAGE_TRANSITION_SMOOTH = "StageTransitionSmooth";


// the direction from which the stage is viewed
const auto ATTRIBUTE_STAGE_VIEW = "StageView";

// the distance from the origin that the center of the stage should be,
// or rather, the distance from the center of the stage that the camera should be 

const auto ATTRIBUTE_STAGE_TOP_DISTANCE = "StageTopDistance";
const auto ATTRIBUTE_STAGE_BACK_DISTANCE = "StageBackDistance";
const auto ATTRIBUTE_STAGE_SIDE_DISTANCE = "StageSideDistance";

const auto ATTRIBUTE_STAGE_ROTATION_SPEED = "StageRotSpeed";
const auto ATTRIBUTE_STAGE_DISTANCE_SPEED = "StageDistSpeed";

const auto ATTRIBUTE_STAGE_PLAYER_START_X = "StageStartX";
const auto ATTRIBUTE_STAGE_PLAYER_START_Y = "StageStartY";
const auto ATTRIBUTE_STAGE_PLAYER_START_Z = "StageStartZ";

// assists with transitioning between stages
// should match the depth dimension created by the stage borders
const auto ATTRIBUTE_STAGE_LENGTH = "StageLength";

// the time elapsed while the stage is active
const auto ATTRIBUTE_STAGE_TIME_ELAPSED = "StageElapsed";
// true if the stage is counting time elapsed
const auto ATTRIBUTE_STAGE_TIME_COUNTING = "StageTimeCounting";


class Stage : public virtual Object_Spatial, public virtual Object_SoundOutput {
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