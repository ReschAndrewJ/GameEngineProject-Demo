#ifndef OBJECT_STAGE_CONTROL
#define OBJECT_STAGE_CONTROL

#include "../../_GameEngineSrc/Objects/Camera/Object_Camera.h"

#include <string>

const auto OBJECT_CLASS_STAGE_CONTROL = "StageControl";

//
const int STAGE_TRANSITION_NONE = 0;
const int STAGE_TRANSITION_STARTSTAGE = 1;
const int STAGE_TRANSITION_ENDSTAGE = 2;
const int STAGE_TRANSITION_FULL = 3;
const int STAGE_TRANSITION_SMOOTH = 4;
const auto ATTRIBUTE_STAGE_CONTROL_TRANSITION_STATE = "StageControlTransitionState";

// the file with the stage that is loaded on transition_startstage
const auto ATTRIBUTE_STAGE_CONTROL_STARTING_STAGE_INST_FILE = "StageControlStartingFile";
// the identifier for the stage that is loaded on transition_startstage
const auto ATTRIBUTE_STAGE_CONTROL_STARTING_STAGE_INST_IDENTIFIER = "StageControlStartingId";

class StageControl : public virtual Object_Camera {
public:
	StageControl();
	virtual ~StageControl();

	static void processFunc(Object*, float);
	
private:

	// sub functiona of processFunc, 
	// called if the current transition state is STAGE_TRANSITION_NONE, STAGE_TRANSITION_SMOOTH, ETC.
	
	void process_transitionNone(float);

	void process_transitionSmooth(float);
	void process_transitionHard(float);

	void process_transitionStartOnly(float);
	void process_transitionEndOnly(float);


	// helper variables
	std::string endingStageId;
	std::string startingStageId;

	float distanceHoldTop = 0;
	float distanceHoldBack = 0;
	float distanceHoldSide = 0;
	bool holdsSet = false;

	float zOffset = 0;
	int playerColliderHold = 0;
	std::string playerId;

};


#endif