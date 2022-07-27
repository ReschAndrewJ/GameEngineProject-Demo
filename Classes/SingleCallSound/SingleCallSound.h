#ifndef SINGLE_CALL_SOUNF
#define SINGLE_CALL_SOUND

#include "../../_GameEngineSrc/Objects/SoundOutput/Object_SoundOutput.h"
#include "../../_GameEngineSrc/Engines/Sound/Sound_Engine.h"

const auto OBJECT_CLASS_SINGLE_CALL_SOUND = "SingleCallSound";

class SingleCallSound : public virtual Object_SoundOutput {
private:
	Sound_Engine* soundEnginePtr;
public:
	SingleCallSound();
	virtual ~SingleCallSound();

	static void afterCreationFunc(Object*);
	static void processFunc(Object*, float);
};


#endif