#ifndef STAGE_BOSS
#define STAGE_BOSS

#include "../Stage/Stage.h"

const auto OBJECT_CLASS_STAGE_BOSS = "Stage_Boss";


class Stage_Boss : public virtual Stage {
public:
	Stage_Boss();
	virtual ~Stage_Boss();

	
	bool isStageComplete() const override;
};


#endif