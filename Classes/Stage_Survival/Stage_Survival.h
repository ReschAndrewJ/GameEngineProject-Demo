#ifndef STAGE_SURVIVAL
#define STAGE_SURVIVAL

#include "../Stage/Stage.h"

// Stage with a set end time

const auto OBJECT_CLASS_STAGE_SURVIVAL = "Stage_Survival";

// how much time should elapse before the stage ends
const auto ATTRIBUTE_STAGE_SURVIVAL_END_TIME = "StageSurvivalEndTime";

class Stage_Survival : public virtual Stage {
public:
	Stage_Survival();
	virtual ~Stage_Survival();

protected:
	bool isStageComplete() const override;
};


#endif