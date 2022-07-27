#include "SingleCallSound.h"

SingleCallSound::SingleCallSound() {
	addClassIdentifier(OBJECT_CLASS_SINGLE_CALL_SOUND);

	addRequestedPointer(PTR_IDENTIFIER::SOUND_ENGINE_PTR, &soundEnginePtr);

	addAfterCreationFunction(&afterCreationFunc);
	addProcessFunction(&processFunc, 10);
}
SingleCallSound::~SingleCallSound() {}

void SingleCallSound::afterCreationFunc(Object* selfptr) {
	dynamic_cast<SingleCallSound*>(selfptr)->play();
}

void SingleCallSound::processFunc(Object* selfptr, float delta) {
	Sound_Engine* soundEnginePtr = dynamic_cast<SingleCallSound*>(selfptr)->soundEnginePtr;

	if (!soundEnginePtr->isAudioPlaying(selfptr->getIdentifier())) 
		selfptr->queueDestroyObject(selfptr->getIdentifier());

}