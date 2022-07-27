#include "Stage.h"
#include "../../General/ViewEnums.h"
#include "../StageBorder/StageBorder.h"

// rotation angles for each stage view
float fromTop[3] = { -90,0,0 };
float fromBack[3] = { 0,0,0 };
float fromSide[3] = { 0,-90,0 };


Stage::Stage() {
	addClassIdentifier(OBJECT_CLASS_STAGE);

	createAttribute(ATTRIBUTE_STAGE_NEXT_FILEPATH, Attribute::types::STRING);
	createAttribute(ATTRIBUTE_STAGE_NEXT_IDENTIFIER, Attribute::types::STRING);
	createAttribute(ATTRIBUTE_STAGE_TRANSITION_SMOOTH, Attribute::types::BOOLEAN);
	createAttribute(ATTRIBUTE_STAGE_COMPLETE, Attribute::types::BOOLEAN);

	createAttribute(ATTRIBUTE_STAGE_VIEW, Attribute::types::INTEGER);
	setAttribute(ATTRIBUTE_STAGE_VIEW, (int)VIEWS::FROM_TOP);

	createAttribute(ATTRIBUTE_STAGE_BACK_DISTANCE, Attribute::types::DOUBLE);
	createAttribute(ATTRIBUTE_STAGE_SIDE_DISTANCE, Attribute::types::DOUBLE);
	createAttribute(ATTRIBUTE_STAGE_TOP_DISTANCE, Attribute::types::DOUBLE);

	createAttribute(ATTRIBUTE_STAGE_ROTATION_SPEED, Attribute::types::DOUBLE);
	createAttribute(ATTRIBUTE_STAGE_DISTANCE_SPEED, Attribute::types::DOUBLE);
	setAttribute(ATTRIBUTE_STAGE_ROTATION_SPEED, 100);
	setAttribute(ATTRIBUTE_STAGE_DISTANCE_SPEED, 500);

	createAttribute(ATTRIBUTE_STAGE_LENGTH, Attribute::types::DOUBLE);

	createAttribute(ATTRIBUTE_STAGE_PLAYER_START_X, Attribute::types::DOUBLE);
	createAttribute(ATTRIBUTE_STAGE_PLAYER_START_Y, Attribute::types::DOUBLE);
	createAttribute(ATTRIBUTE_STAGE_PLAYER_START_Z, Attribute::types::DOUBLE);

	createAttribute(ATTRIBUTE_STAGE_TIME_ELAPSED, Attribute::types::DOUBLE);
	createAttribute(ATTRIBUTE_STAGE_TIME_COUNTING, Attribute::types::BOOLEAN);
	setAttribute(ATTRIBUTE_STAGE_TIME_COUNTING, true);

	addAfterCreationFunction(&afterCreationFunc);
	addProcessFunction(&processFunc, 10);
}
Stage::~Stage() {}


void Stage::afterCreationFunc(Object* selfptr) {
	VIEWS view = (VIEWS)(int)selfptr->getAttribute(ATTRIBUTE_STAGE_VIEW);
	switch (view)
	{
	case VIEWS::FROM_TOP:
		selfptr->setAttribute(ATTRIBUTE_SPATIAL_ROTATE_NOD, fromTop[0]);
		selfptr->setAttribute(ATTRIBUTE_SPATIAL_ROTATE_TURN, fromTop[1]);
		selfptr->setAttribute(ATTRIBUTE_SPATIAL_ROTATE_TILT, fromTop[2]);
		selfptr->setAttribute(ATTRIBUTE_SPATIAL_POSITION_Z, 
			-(float)selfptr->getAttribute(ATTRIBUTE_STAGE_TOP_DISTANCE));
		break;
	case VIEWS::FROM_SIDE:
		selfptr->setAttribute(ATTRIBUTE_SPATIAL_ROTATE_NOD, fromSide[0]);
		selfptr->setAttribute(ATTRIBUTE_SPATIAL_ROTATE_TURN, fromSide[1]);
		selfptr->setAttribute(ATTRIBUTE_SPATIAL_ROTATE_TILT, fromSide[2]);
		selfptr->setAttribute(ATTRIBUTE_SPATIAL_POSITION_Z,
			-(float)selfptr->getAttribute(ATTRIBUTE_STAGE_SIDE_DISTANCE));
		break;
	case VIEWS::FROM_BACK:
		selfptr->setAttribute(ATTRIBUTE_SPATIAL_ROTATE_NOD, fromBack[0]);
		selfptr->setAttribute(ATTRIBUTE_SPATIAL_ROTATE_TURN, fromBack[1]);
		selfptr->setAttribute(ATTRIBUTE_SPATIAL_ROTATE_TILT, fromBack[2]);
		selfptr->setAttribute(ATTRIBUTE_SPATIAL_POSITION_Z,
			-(float)selfptr->getAttribute(ATTRIBUTE_STAGE_BACK_DISTANCE));
		break;
	default:
		selfptr->setAttribute(ATTRIBUTE_SPATIAL_ROTATE_NOD, fromTop[0]);
		selfptr->setAttribute(ATTRIBUTE_SPATIAL_ROTATE_TURN, fromTop[1]);
		selfptr->setAttribute(ATTRIBUTE_SPATIAL_ROTATE_TILT, fromTop[2]);
		selfptr->setAttribute(ATTRIBUTE_SPATIAL_POSITION_Z,
			-(float)selfptr->getAttribute(ATTRIBUTE_STAGE_TOP_DISTANCE));
		break;
	}

}


void Stage::processFunc(Object* selfptr, float delta) {
	// update elapsed time
	if ((bool)selfptr->getAttribute(ATTRIBUTE_STAGE_TIME_COUNTING)) selfptr->setAttribute(
		ATTRIBUTE_STAGE_TIME_ELAPSED, (float)selfptr->getAttribute(ATTRIBUTE_STAGE_TIME_ELAPSED) + delta);
	// check if stage is completed and update completion attribute
	if (dynamic_cast<Stage*>(selfptr)->isStageComplete()) selfptr->setAttribute(ATTRIBUTE_STAGE_COMPLETE, true);
	
	float nod = selfptr->getAttribute(ATTRIBUTE_SPATIAL_ROTATE_NOD);
	float turn = selfptr->getAttribute(ATTRIBUTE_SPATIAL_ROTATE_TURN);
	float tilt = selfptr->getAttribute(ATTRIBUTE_SPATIAL_ROTATE_TILT);

	VIEWS view = (VIEWS)(int)selfptr->getAttribute(ATTRIBUTE_STAGE_VIEW);
	float targetAngles[3]{};
	switch (view)
	{
	case VIEWS::FROM_TOP:
		targetAngles[0] = fromTop[0]; targetAngles[1] = fromTop[1]; targetAngles[2] = fromTop[2];
		break;
	case VIEWS::FROM_SIDE:
		targetAngles[0] = fromSide[0]; targetAngles[1] = fromSide[1]; targetAngles[2] = fromSide[2];
		break;
	case VIEWS::FROM_BACK:
		targetAngles[0] = fromBack[0]; targetAngles[1] = fromBack[1]; targetAngles[2] = fromBack[2];
		break;
	default:
		targetAngles[0] = fromTop[0]; targetAngles[1] = fromTop[1]; targetAngles[2] = fromTop[2];
		break;
	}
	for (const auto& childId : selfptr->getChildrenIdentifiers()) {
		Object* childPtr = selfptr->getObject(childId);
		if (childPtr->is_class(OBJECT_CLASS_STAGE_BORDER)) {
			int side = childPtr->getAttribute(ATTRIBUTE_STAGE_BORDER_SIDE);

			childPtr->setAttribute(ATTRIBUTE_SPRITE_VISIBLE, true);
			switch (side) {
			case STAGE_BORDER_TOP:
				if (nod <= -45) childPtr->setAttribute(ATTRIBUTE_SPRITE_VISIBLE, false);
				break;
			case STAGE_BORDER_RIGHT:
				if (turn <= -45) childPtr->setAttribute(ATTRIBUTE_SPRITE_VISIBLE, false);
				break;
			case STAGE_BORDER_FRONT:
				if (nod >= -45 && turn >= -45) childPtr->setAttribute(ATTRIBUTE_SPRITE_VISIBLE, false);
				break;
			default:
				break;
			}

		}
	}


	float dist = selfptr->getAttribute(ATTRIBUTE_SPATIAL_POSITION_Z);
	float targetDist;
	switch (view)
	{
	case VIEWS::FROM_TOP:
		targetDist = -(float)selfptr->getAttribute(ATTRIBUTE_STAGE_TOP_DISTANCE);
		break;
	case VIEWS::FROM_SIDE:
		targetDist = -(float)selfptr->getAttribute(ATTRIBUTE_STAGE_SIDE_DISTANCE);
		break;
	case VIEWS::FROM_BACK:
		targetDist = -(float)selfptr->getAttribute(ATTRIBUTE_STAGE_BACK_DISTANCE);
		break;
	default:
		targetDist = -(float)selfptr->getAttribute(ATTRIBUTE_STAGE_TOP_DISTANCE);
		break;
	}

	float diff = targetDist - dist;
	float newDist = dist;

	float diffs[3] = { targetAngles[0] - nod, targetAngles[1] - turn, targetAngles[2] - tilt };
	float newAngles[3]{nod, turn, tilt};
	
	float rotSpeed = selfptr->getAttribute(ATTRIBUTE_STAGE_ROTATION_SPEED);
	float distSpeed = selfptr->getAttribute(ATTRIBUTE_STAGE_DISTANCE_SPEED);

	if (diff <= 0) { // rotate before move
		bool nodDiff = abs(diffs[0]) > rotSpeed * delta;
		bool turnDiff = abs(diffs[1]) > rotSpeed * delta;
		bool tiltDiff = abs(diffs[2]) > rotSpeed * delta;
		if ( nodDiff || turnDiff || tiltDiff ) { // rotate
			if (nodDiff) newAngles[0] = nod + diffs[0] / abs(diffs[0]) * rotSpeed * delta;
			else newAngles[0] = targetAngles[0];
			if (turnDiff) newAngles[1] = turn + diffs[1] / abs(diffs[1]) * rotSpeed * delta;
			else newAngles[1] = targetAngles[1];
			if (tiltDiff) newAngles[2] = tilt + diffs[2] / abs(diffs[2]) * rotSpeed * delta;
			else newAngles[2] = targetAngles[2];
		}
		else { // move if rotation is complete
			if (abs(diff) > distSpeed * delta) newDist = dist + diff / abs(diff) * distSpeed * delta;
			else newDist = targetDist;
			newAngles[0] = targetAngles[0];
			newAngles[1] = targetAngles[1];
			newAngles[2] = targetAngles[2];
		}
	}
	else { // move before rotate
		if (abs(diff) > distSpeed * delta) newDist = dist + diff / abs(diff) * distSpeed * delta;
		else newDist = targetDist;
	}

	selfptr->setAttribute(ATTRIBUTE_SPATIAL_POSITION_Z, newDist);

	selfptr->setAttribute(ATTRIBUTE_SPATIAL_ROTATE_NOD, newAngles[0]);
	selfptr->setAttribute(ATTRIBUTE_SPATIAL_ROTATE_TURN, newAngles[1]);
	selfptr->setAttribute(ATTRIBUTE_SPATIAL_ROTATE_TILT, newAngles[2]);
	

}




