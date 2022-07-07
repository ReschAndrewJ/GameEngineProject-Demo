#ifndef OBJECT_STAGE_CONTROL
#define OBJECT_STAGE_CONTROL

#include "GameEngineLib/Objects/Camera/Object_Camera.h"

class StageControl : public virtual Object_Camera {
public:
	StageControl();
	virtual ~StageControl();

	static void processFunc(Object*, float);

private:
	void startStage();
	void endStage();
	// load the next stage before unloading the completed one, 
	// temporaily move the player to stage control to not reset the player
	void transitionStage_Smooth();
	// fade first stage to black then fade second stage in
	void transitionStage_Hard();



};


#endif