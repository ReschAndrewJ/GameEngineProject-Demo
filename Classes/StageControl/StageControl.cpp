#include "StageControl.h"

#include "../Stage/Stage.h"
#include "../../General/ViewEnums.h"
#include "../Player/Player.h"
#include "../SpawnInfo/SpawnInfo.h"
#include "../DespawnBox/DespawnBox.h"

StageControl::StageControl() {
	addClassIdentifier(OBJECT_CLASS_STAGE_CONTROL);

	createAttribute(ATTRIBUTE_STAGE_CONTROL_TRANSITION_STATE, Attribute::types::INTEGER);
	setAttribute(ATTRIBUTE_STAGE_CONTROL_TRANSITION_STATE, STAGE_TRANSITION_NONE);
	createAttribute(ATTRIBUTE_STAGE_CONTROL_STARTING_STAGE_INST_FILE, Attribute::types::STRING);
	createAttribute(ATTRIBUTE_STAGE_CONTROL_STARTING_STAGE_INST_IDENTIFIER, Attribute::types::STRING);

	addProcessFunction(&processFunc, 15);
}
StageControl::~StageControl() {}



void StageControl::processFunc(Object* selfptr, float delta) {

	int transitionState = selfptr->getAttribute(ATTRIBUTE_STAGE_CONTROL_TRANSITION_STATE);
	
	switch (transitionState) {
	case STAGE_TRANSITION_NONE: // no transition
		dynamic_cast<StageControl*>(selfptr)->process_transitionNone(delta);
		break;
	case STAGE_TRANSITION_STARTSTAGE: // start only
		dynamic_cast<StageControl*>(selfptr)->process_transitionStartOnly(delta);
		break;
	case STAGE_TRANSITION_ENDSTAGE: // end only
		dynamic_cast<StageControl*>(selfptr)->process_transitionEndOnly(delta);
		break;
	case STAGE_TRANSITION_FULL: // hard transition

		break;
	case STAGE_TRANSITION_SMOOTH: // smooth transition
		dynamic_cast<StageControl*>(selfptr)->process_transitionSmooth(delta);
		break;
	default: // invalid transition state, reset attribute
		selfptr->setAttribute(ATTRIBUTE_STAGE_CONTROL_TRANSITION_STATE, STAGE_TRANSITION_NONE);
		break;
	}
	

}


void StageControl::process_transitionNone(float delta) {
	for (const auto& childId : getChildrenIdentifiers()) {
		
		Object* stagePtr = getObject(childId);
		// check if child object is stage and is complete
		if (stagePtr->is_class(OBJECT_CLASS_STAGE)
			&& (bool)stagePtr->getAttribute(ATTRIBUTE_STAGE_COMPLETE)) {

			endingStageId = childId;

			// stage has transition information
			std::string nextStageId = stagePtr->getAttribute(ATTRIBUTE_STAGE_NEXT_IDENTIFIER);
			std::string nextStagePath = stagePtr->getAttribute(ATTRIBUTE_STAGE_NEXT_FILEPATH);
			if (!nextStageId.empty() && !nextStagePath.empty()) {
				
				// smooth transition
				if ((bool)stagePtr->getAttribute(ATTRIBUTE_STAGE_TRANSITION_SMOOTH)) {
					setAttribute(ATTRIBUTE_STAGE_CONTROL_TRANSITION_STATE,
						STAGE_TRANSITION_SMOOTH);
				}
				// hard transition
				else {
					setAttribute(ATTRIBUTE_STAGE_CONTROL_TRANSITION_STATE, 
						STAGE_TRANSITION_FULL);
				}
			}
			// stage does not have transition information
			else {
				setAttribute(ATTRIBUTE_STAGE_CONTROL_TRANSITION_STATE, 
					STAGE_TRANSITION_ENDSTAGE);
			}
}}}



void StageControl::process_transitionSmooth(float delta) {
	int transitionState = getAttribute(ATTRIBUTE_STAGE_CONTROL_TRANSITION_STATE);
	Object* endingStage = getObject(endingStageId);
	
	if (endingStage == nullptr) { 
		setAttribute(ATTRIBUTE_STAGE_CONTROL_TRANSITION_STATE, STAGE_TRANSITION_NONE);
		return;
	}

	if (startingStageId.empty()) {
		holdsSet = false;

		// check if starting stage has been created
		for (const auto& childId : getChildrenIdentifiers()) 
			if (childId != endingStageId && getObject(childId)->is_class(OBJECT_CLASS_STAGE)) {
				startingStageId = childId;
				if ((int)getObject(startingStageId)->getAttribute(ATTRIBUTE_STAGE_VIEW) == (int)VIEWS::DONT_MIND) {
					getObject(startingStageId)->setAttribute(ATTRIBUTE_STAGE_VIEW,
						endingStage->getAttribute(ATTRIBUTE_STAGE_VIEW));
					Stage::afterCreationFunc(getObject(startingStageId));
				}
				else {
					endingStage->setAttribute(ATTRIBUTE_STAGE_VIEW,
						getObject(startingStageId)->getAttribute(ATTRIBUTE_STAGE_VIEW));
				}

				// move despawn boxes before they remove any objects
				for (const auto& stageChildId : getObject(startingStageId)->getChildrenIdentifiers()) {
					Object* stageChildPtr = getObject(stageChildId);
					if (stageChildPtr->is_class(OBJECT_CLASS_DESPAWN_BOX)) {
						for (const auto& border : stageChildPtr->getChildrenIdentifiers()) {
							getObject(border)->setAttribute(ATTRIBUTE_COLLIDER_MASK_TARGET, 0);
						}
					}
				}
				for (const auto& stageChildId : endingStage->getChildrenIdentifiers()) {
					Object* stageChildPtr = getObject(stageChildId);
					if (stageChildPtr->is_class(OBJECT_CLASS_DESPAWN_BOX)) {
						for (const auto& border : stageChildPtr->getChildrenIdentifiers()) {
							getObject(border)->setAttribute(ATTRIBUTE_COLLIDER_MASK_TARGET, 0);
						}
					}
				}
				break;
			}
		// else queue starting stage creation
		if (startingStageId.empty()) queueCreateObject(
			endingStage->getAttribute(ATTRIBUTE_STAGE_NEXT_FILEPATH),
			endingStage->getAttribute(ATTRIBUTE_STAGE_NEXT_IDENTIFIER), getIdentifier(),
			{ {ATTRIBUTE_SPATIAL_POSITION_Y, 99999999},
			{ATTRIBUTE_STAGE_TIME_COUNTING, false} }
			// set the position far away to not show the starting stage on the first instanced frame 
		);

		return;
	}
	
	Object* startingStage = getObject(startingStageId);
	
	if (!holdsSet) {
		distanceHoldBack = startingStage->getAttribute(ATTRIBUTE_STAGE_BACK_DISTANCE);
		distanceHoldSide = startingStage->getAttribute(ATTRIBUTE_STAGE_SIDE_DISTANCE);
		distanceHoldTop = startingStage->getAttribute(ATTRIBUTE_STAGE_TOP_DISTANCE);

		zOffset = (float)endingStage->getAttribute(ATTRIBUTE_STAGE_LENGTH) / 2
			+ (float)startingStage->getAttribute(ATTRIBUTE_STAGE_LENGTH) / 2 + 1;
		zOffset *= -1; // positive z is towards the screen, negative is away
		for (const auto& childId : startingStage->getChildrenIdentifiers()) {
			Object* childPtr = getObject(childId);
			if (childPtr->is_class(OBJECT_CLASS_SPATIAL))
				childPtr->setAttribute(ATTRIBUTE_SPATIAL_POSITION_Z,
					(float)childPtr->getAttribute(ATTRIBUTE_SPATIAL_POSITION_Z) + zOffset);
		}
		//startingStage->setAttribute(ATTRIBUTE_SPATIAL_POSITION_Y, 0);
		
		for (const auto& childId : endingStage->getChildrenIdentifiers()) {
			Object* childPtr = getObject(childId); 
			if (childPtr->is_class(OBJECT_CLASS_PLAYER)) {
				playerId = childId; 
				playerColliderHold = childPtr->getAttribute(ATTRIBUTE_COLLIDER_MASK_TARGET);
				childPtr->setAttribute(ATTRIBUTE_COLLIDER_MASK_TARGET, 0);
			}
		}

		holdsSet = true;

		// shrink ending stage distances for smoother transition
		if ((int)endingStage->getAttribute(ATTRIBUTE_STAGE_BACK_DISTANCE)
		> (int)startingStage->getAttribute(ATTRIBUTE_STAGE_BACK_DISTANCE)) {
			endingStage->setAttribute(ATTRIBUTE_STAGE_BACK_DISTANCE,
				startingStage->getAttribute(ATTRIBUTE_STAGE_BACK_DISTANCE));
		}
		else {
			startingStage->setAttribute(ATTRIBUTE_STAGE_BACK_DISTANCE,
				endingStage->getAttribute(ATTRIBUTE_STAGE_BACK_DISTANCE));
		}
		if ((int)endingStage->getAttribute(ATTRIBUTE_STAGE_SIDE_DISTANCE)
		> (int)startingStage->getAttribute(ATTRIBUTE_STAGE_SIDE_DISTANCE)) {
			endingStage->setAttribute(ATTRIBUTE_STAGE_SIDE_DISTANCE,
				startingStage->getAttribute(ATTRIBUTE_STAGE_SIDE_DISTANCE));
		}
		else {
			startingStage->setAttribute(ATTRIBUTE_STAGE_SIDE_DISTANCE,
				endingStage->getAttribute(ATTRIBUTE_STAGE_SIDE_DISTANCE));
		}
		if ((int)endingStage->getAttribute(ATTRIBUTE_STAGE_TOP_DISTANCE)
		> (int)startingStage->getAttribute(ATTRIBUTE_STAGE_TOP_DISTANCE)) {
			endingStage->setAttribute(ATTRIBUTE_STAGE_TOP_DISTANCE,
				startingStage->getAttribute(ATTRIBUTE_STAGE_TOP_DISTANCE));
		}
		else {
			startingStage->setAttribute(ATTRIBUTE_STAGE_TOP_DISTANCE,
				endingStage->getAttribute(ATTRIBUTE_STAGE_TOP_DISTANCE));
		}

		startingStage->setAttribute(ATTRIBUTE_SPATIAL_POSITION_Z,
			endingStage->getAttribute(ATTRIBUTE_SPATIAL_POSITION_Z));
	

		float startingStageBGMVolume = startingStage->getAttribute(ATTRIBUTE_SOUND_VOLUME);

		// switch bgm if different
		if ((std::string)startingStage->getAttribute(ATTRIBUTE_SOUND_FILE) ==
			(std::string)endingStage->getAttribute(ATTRIBUTE_SOUND_FILE)) {
			startingStage->setAttribute(ATTRIBUTE_SOUND_START_OFFSET, dynamic_cast<Stage*>(endingStage)->getOffset());
		}
		dynamic_cast<Stage*>(endingStage)->stop();
		startingStage->setAttribute(ATTRIBUTE_SOUND_VOLUME, startingStageBGMVolume);
		dynamic_cast<Stage*>(startingStage)->play();

	}

	

	// move player object to center
	if (zOffset != 0) {
		Object* playerPtr = getObject(playerId);
		float pos[3] = { 
			playerPtr->getAttribute(ATTRIBUTE_SPATIAL_POSITION_X),
			playerPtr->getAttribute(ATTRIBUTE_SPATIAL_POSITION_Y),
			playerPtr->getAttribute(ATTRIBUTE_SPATIAL_POSITION_Z)};
		float speed = (float)playerPtr->getAttribute(ATTRIBUTE_LIVE_ENTITY_MOVE_SPEED) * 2;

		// X
		if (abs(pos[0]) > speed * delta)
			playerPtr->setAttribute(ATTRIBUTE_SPATIAL_POSITION_X,
				pos[0] - speed * delta * (signbit(pos[0]) ? -1 : 1)
			);
		else playerPtr->setAttribute(ATTRIBUTE_SPATIAL_POSITION_X, 0);
		// Y
		if (abs(pos[1]) > speed * delta)
			playerPtr->setAttribute(ATTRIBUTE_SPATIAL_POSITION_Y,
				pos[1] - speed * delta * (signbit(pos[1]) ? -1 : 1)
			);
		else playerPtr->setAttribute(ATTRIBUTE_SPATIAL_POSITION_Y, 0);
		// Z
		if (abs(pos[2]) > speed * delta)
			playerPtr->setAttribute(ATTRIBUTE_SPATIAL_POSITION_Z,
				pos[2] - speed * delta * (signbit(pos[2]) ? -1 : 1)
			);
		else playerPtr->setAttribute(ATTRIBUTE_SPATIAL_POSITION_Z, 0);
	}

	// match stage rotations before positioning the stages
	if ((float)endingStage->getAttribute(ATTRIBUTE_SPATIAL_ROTATE_NOD) !=
		(float)startingStage->getAttribute(ATTRIBUTE_SPATIAL_ROTATE_NOD) ||
		(float)endingStage->getAttribute(ATTRIBUTE_SPATIAL_ROTATE_TILT) !=
		(float)startingStage->getAttribute(ATTRIBUTE_SPATIAL_ROTATE_TILT) ||
		(float)endingStage->getAttribute(ATTRIBUTE_SPATIAL_ROTATE_TURN) !=
		(float)startingStage->getAttribute(ATTRIBUTE_SPATIAL_ROTATE_TURN)) {
		return;
	}

	// after view positions are transitioned, transition both stages' position offsets
	if (zOffset != 0 &&
		abs((float)endingStage->getAttribute(ATTRIBUTE_SPATIAL_POSITION_Z)
		- (float)startingStage->getAttribute(ATTRIBUTE_SPATIAL_POSITION_Z)) 
		< delta * (float)endingStage->getAttribute(ATTRIBUTE_STAGE_DISTANCE_SPEED) 
		&&
		(float)endingStage->getAttribute(ATTRIBUTE_SPATIAL_ROTATE_NOD) 
		- (float)startingStage->getAttribute(ATTRIBUTE_SPATIAL_ROTATE_NOD)
		< delta * (float)endingStage->getAttribute(ATTRIBUTE_STAGE_DISTANCE_SPEED)
		&& 
		(float)endingStage->getAttribute(ATTRIBUTE_SPATIAL_ROTATE_TURN)
		- (float)startingStage->getAttribute(ATTRIBUTE_SPATIAL_ROTATE_TURN)
		< delta * (float)endingStage->getAttribute(ATTRIBUTE_STAGE_DISTANCE_SPEED) 
		&&
		(float)endingStage->getAttribute(ATTRIBUTE_SPATIAL_ROTATE_TILT)
		- (float)startingStage->getAttribute(ATTRIBUTE_SPATIAL_ROTATE_TILT)
		< delta * (float)endingStage->getAttribute(ATTRIBUTE_STAGE_DISTANCE_SPEED))
	{
		startingStage->setAttribute(ATTRIBUTE_SPATIAL_POSITION_Y, 0);

		float speed = startingStage->getAttribute(ATTRIBUTE_STAGE_DISTANCE_SPEED);
		float newZOffset = zOffset + delta * speed;
		if (abs(newZOffset) < delta * speed)
			newZOffset = 0;
		for (const auto& childId : startingStage->getChildrenIdentifiers()) {
			Object* childPtr = getObject(childId);
			if (childPtr->is_class(OBJECT_CLASS_SPATIAL)) {
				
				childPtr->setAttribute(ATTRIBUTE_SPATIAL_POSITION_Z, 
					(float)childPtr->getAttribute(ATTRIBUTE_SPATIAL_POSITION_Z) - zOffset + newZOffset);

			}
		}
		for (const auto& childId : endingStage->getChildrenIdentifiers()) {
			Object* childPtr = getObject(childId);
			if (childPtr->is_class(OBJECT_CLASS_SPATIAL) && !childPtr->is_class(OBJECT_CLASS_PLAYER)) {

				childPtr->setAttribute(ATTRIBUTE_SPATIAL_POSITION_Z,
					(float)childPtr->getAttribute(ATTRIBUTE_SPATIAL_POSITION_Z) - zOffset + newZOffset);

			}
		}
		zOffset = newZOffset;
	}

	// after offsets are transitioned, transition starting stage's view position
	if (zOffset == 0) {
		startingStage->setAttribute(ATTRIBUTE_STAGE_BACK_DISTANCE, distanceHoldBack);
		startingStage->setAttribute(ATTRIBUTE_STAGE_SIDE_DISTANCE, distanceHoldSide);
		startingStage->setAttribute(ATTRIBUTE_STAGE_TOP_DISTANCE, distanceHoldTop);
		
		float targetPos[3] = {
			startingStage->getAttribute(ATTRIBUTE_STAGE_PLAYER_START_X),
			startingStage->getAttribute(ATTRIBUTE_STAGE_PLAYER_START_Y),
			startingStage->getAttribute(ATTRIBUTE_STAGE_PLAYER_START_Z)};

		Object* playerPtr = getObject(playerId);

		float diff[3] = {
			targetPos[0] - (float)playerPtr->getAttribute(ATTRIBUTE_SPATIAL_POSITION_X),
			targetPos[1] - (float)playerPtr->getAttribute(ATTRIBUTE_SPATIAL_POSITION_Y),
			targetPos[2] - (float)playerPtr->getAttribute(ATTRIBUTE_SPATIAL_POSITION_Z)};
		float speed = (float)playerPtr->getAttribute(ATTRIBUTE_LIVE_ENTITY_MOVE_SPEED) * 2;
		

		// X
		if (abs(diff[0]) > speed * delta)
			playerPtr->setAttribute(ATTRIBUTE_SPATIAL_POSITION_X,
				(float)playerPtr->getAttribute(ATTRIBUTE_SPATIAL_POSITION_X) 
				+ speed * delta * (signbit(diff[0]) ? -1 : 1)
			);
		else playerPtr->setAttribute(ATTRIBUTE_SPATIAL_POSITION_X, targetPos[0]);

		// Y
		if (abs(diff[1]) > speed * delta)
			playerPtr->setAttribute(ATTRIBUTE_SPATIAL_POSITION_Y,
				(float)playerPtr->getAttribute(ATTRIBUTE_SPATIAL_POSITION_Y) 
				+ speed * delta * (signbit(diff[1]) ? -1 : 1)
			);
		else playerPtr->setAttribute(ATTRIBUTE_SPATIAL_POSITION_Y, targetPos[1]);

		// Z
		if (abs(diff[2]) > speed * delta)
			playerPtr->setAttribute(ATTRIBUTE_SPATIAL_POSITION_Z,
				(float)playerPtr->getAttribute(ATTRIBUTE_SPATIAL_POSITION_Z) 
				+ speed * delta * (signbit(diff[2]) ? -1 : 1)
			);
		else playerPtr->setAttribute(ATTRIBUTE_SPATIAL_POSITION_Z, targetPos[2]);

		if (abs(diff[0]) > speed * delta || abs(diff[1]) > speed * delta || abs(diff[2]) > speed * delta) return;


		playerPtr->setAttribute(ATTRIBUTE_COLLIDER_MASK_TARGET, playerColliderHold);
		playerPtr->changeParentObject(startingStageId);
		
		for (const auto& childId : startingStage->getChildrenIdentifiers()) {
			Object* childPtr = getObject(childId);
			if (childPtr->is_class(OBJECT_CLASS_SPAWN_INFO)) {
				dynamic_cast<SpawnInfo*>(childPtr)->startTimer();
			}
			if (childPtr->is_class(OBJECT_CLASS_DESPAWN_BOX)) {
				for (const auto& border : childPtr->getChildrenIdentifiers()) {
					getObject(border)->setAttribute(ATTRIBUTE_COLLIDER_MASK_TARGET, 255);
				}
			}
		}

		// finish stage transition
		queueDestroyObject(endingStageId);
		startingStage->setAttribute(ATTRIBUTE_STAGE_TIME_COUNTING, true);
		setAttribute(ATTRIBUTE_STAGE_CONTROL_TRANSITION_STATE, STAGE_TRANSITION_NONE);
		endingStageId = "";
		startingStageId = "";
		playerId = "";
	}

}



void StageControl::process_transitionStartOnly(float delta) {
	// verify that there is a starting stage
	if (((std::string)getAttribute(ATTRIBUTE_STAGE_CONTROL_STARTING_STAGE_INST_FILE)).empty()
		|| ((std::string)getAttribute(ATTRIBUTE_STAGE_CONTROL_STARTING_STAGE_INST_IDENTIFIER)).empty()) {
		setAttribute(ATTRIBUTE_STAGE_CONTROL_TRANSITION_STATE, STAGE_TRANSITION_NONE);
		return;
	}

	// add the starting stage if it is not added yet
	if (startingStageId.empty()) {
		for (auto& childId : getChildrenIdentifiers()) if (getObject(childId)->is_class(OBJECT_CLASS_STAGE)) {
			startingStageId = childId;
			break;
		}
		if (startingStageId.empty()) queueCreateObject(
			getAttribute(ATTRIBUTE_STAGE_CONTROL_STARTING_STAGE_INST_FILE),
			getAttribute(ATTRIBUTE_STAGE_CONTROL_STARTING_STAGE_INST_IDENTIFIER), getIdentifier(), {}
		);

		return;
	}

	Object* startingStage = getObject(startingStageId);
	// move the player instance from control to the stage
	for (auto& childId : getChildrenIdentifiers()) {
		if (getObject(childId)->is_class(OBJECT_CLASS_PLAYER)) {
			Object* childptr = getObject(childId);
			
			childptr->changeParentObject(startingStageId);
			childptr->setAttribute(ATTRIBUTE_SPATIAL_POSITION_X,
				startingStage->getAttribute(ATTRIBUTE_STAGE_PLAYER_START_X));
			childptr->setAttribute(ATTRIBUTE_SPATIAL_POSITION_Y,
				startingStage->getAttribute(ATTRIBUTE_STAGE_PLAYER_START_Y));
			childptr->setAttribute(ATTRIBUTE_SPATIAL_POSITION_Z,
				startingStage->getAttribute(ATTRIBUTE_STAGE_PLAYER_START_Z));
			break;
		}
	}
	for (auto& childId : startingStage->getChildrenIdentifiers()) {
		if (getObject(childId)->is_class(OBJECT_CLASS_SPAWN_INFO)) {
			dynamic_cast<SpawnInfo*>(getObject(childId))->startTimer();
		}
	}
	dynamic_cast<Stage*>(startingStage)->play();
	setAttribute(ATTRIBUTE_STAGE_CONTROL_TRANSITION_STATE, STAGE_TRANSITION_NONE);
	startingStageId = "";
}


void StageControl::process_transitionEndOnly(float delta) {
	// move the player instance from the stage to control
	for (auto& childId : getChildrenIdentifiers()) {
		if (getObject(childId)->is_class(OBJECT_CLASS_PLAYER)) {
			getObject(childId)->changeParentObject(getIdentifier());
			getObject(childId)->setAttribute(ATTRIBUTE_SPATIAL_POSITION_Y, 9999999);
		}
		if (getObject(childId)->is_class(OBJECT_CLASS_STAGE)) {
			queueDestroyObject(childId);
		}
	}
	setAttribute(ATTRIBUTE_STAGE_CONTROL_TRANSITION_STATE, STAGE_TRANSITION_NONE);
	
	queueDestroyObject(getIdentifier());
	
}