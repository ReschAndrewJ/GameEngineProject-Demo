//#define SAMPLERUNSTAGE
#ifdef SAMPLERUNSTAGE


#include "../_GameEngineSrc/Engines/Main/Main_Engine.h"
#include "../General/KeysToPoll.h"

#include "../Classes/Player/Player.h"
#include "../Classes/Stage/Stage.h"
#include "../Classes/StageBorder/StageBorder.h"
#include "../Classes/StageControl/StageControl.h"
#include "../Classes/Timer/Timer.h"

#include "../General/ViewEnums.h"

const auto ROT_TEST_STAGE = "RotSampleStage";
class rotStage : public virtual Stage {
	Input_Handler* inputptr;
public:
	rotStage() {
		addClassIdentifier(ROT_TEST_STAGE);
		addRequestedPointer(PTR_IDENTIFIER::INPUT_HANDLER_PTR, &inputptr);
		addProcessFunction(&processFunc, 9);
	}
	virtual ~rotStage() {}
	static void processFunc(Object* selfptr, float delta) {
		if (dynamic_cast<rotStage*>(selfptr)->inputptr->getKeyState(keys::Up, input_states::JUST_PRESSED)) {
			selfptr->setAttribute(ATTRIBUTE_STAGE_VIEW, (int)VIEWS::FROM_TOP);
		}
		if (dynamic_cast<rotStage*>(selfptr)->inputptr->getKeyState(keys::Down, input_states::JUST_PRESSED)) {
			selfptr->setAttribute(ATTRIBUTE_STAGE_VIEW, (int)VIEWS::FROM_BACK);
		}
		if (dynamic_cast<rotStage*>(selfptr)->inputptr->getKeyState(keys::Right, input_states::JUST_PRESSED)) {
			selfptr->setAttribute(ATTRIBUTE_STAGE_VIEW, (int)VIEWS::FROM_SIDE);
		}
	}

protected:
	bool isStageComplete() const override {
		if (inputptr->getKeyState(keys::Enter, input_states::JUST_PRESSED)) {
			return true;
		}
		return false;
	}
};


engine_start_info startInfo{};


int main() {
	for (const auto& pair : keys::keysToPoll) {
		startInfo.keysToPoll.push_back(pair);
	}
	startInfo.rootObject_filePath = "sampleRunStage/sampleRunStage.inst";
	startInfo.rootObject_objectName = "Control";

	startInfo.aspectRatioHeight = 1;
	startInfo.aspectRatioWidth = 1;
	startInfo.windowHeight = 600;
	startInfo.windowWidth = 600;

	startInfo.AddedObjectCreateFunctions.push_back({ OBJECT_CLASS_PLAYER, [] { return (Object*)new Player(); } });
	startInfo.AddedObjectCreateFunctions.push_back({ OBJECT_CLASS_STAGE_BORDER, [] { return (Object*)new StageBorder(); } });
	startInfo.AddedObjectCreateFunctions.push_back({ OBJECT_CLASS_STAGE_CONTROL, [] { return (Object*)new StageControl(); } });
	startInfo.AddedObjectCreateFunctions.push_back({ OBJECT_CLASS_TIMER, [] {return (Object*)new Timer(); } });

	startInfo.AddedObjectCreateFunctions.push_back({ ROT_TEST_STAGE, [] { return (Object*)new rotStage(); } });


	Main_Engine e;
	e.start(startInfo);

}



#endif