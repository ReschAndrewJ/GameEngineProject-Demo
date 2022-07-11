#include "StageControl.h"




StageControl::StageControl() {
	addClassIdentifier(OBJECT_CLASS_STAGE_CONTROL);

	addProcessFunction(&processFunc, 15);
}
StageControl::~StageControl() {}



void StageControl::processFunc(Object* selfptr, float delta) {

	
}
