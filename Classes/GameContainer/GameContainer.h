#ifndef OBJECT_GAME_CONTAINER
#define OBJECT_GAME_CONTAINER


#include "../../_GameEngineSrc/Objects/Base/Object.h"

const auto OBJECT_CLASS_GAME_CONTAINER = "GameContainer";


class GameContainer : public virtual Object {
public:
	GameContainer();
	virtual ~GameContainer();

	static void process_func(Object*, float);

};



#endif