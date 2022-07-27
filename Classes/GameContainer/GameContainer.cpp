#include "GameContainer.h"

#include "../StageControl/StageControl.h"

GameContainer::GameContainer() {
	addClassIdentifier(OBJECT_CLASS_GAME_CONTAINER);

	addProcessFunction(&process_func, 1);
}
GameContainer::~GameContainer() {}


void GameContainer::process_func(Object* selfptr, float delta) {
	bool hasStageControl = false;
	for (const auto& childId : selfptr->getChildrenIdentifiers()) {
		if (selfptr->getObject(childId)->is_class(OBJECT_CLASS_STAGE_CONTROL)) {
			hasStageControl = true;
			break;
		}
	}

	if (!hasStageControl) selfptr->queueDestroyObject(selfptr->getIdentifier());
}


