#ifndef OBJECT_TIMER
#define OBJECT_TIMER

#include "../../_GameEngineSrc/Objects/Base/Object.h"

const auto OBJECT_CLASS_TIMER = "Timer";

const auto ATTRIBUTE_TIMER_LENGTH = "TimerLength";
const auto ATTRIBUTE_TIMER_OFFSET = "TimerOffset";
// timeout is true when TimerOffset reaches TimerLength
// is set to false during the process function call of the next frame
const auto ATTRIBUTE_TIMER_TIMEOUT = "TimerTimeout";
const auto ATTRIBUTE_TIMER_LOOP = "TimerLoop";
// true if the timer is currently running
const auto ATTRIBUTE_TIMER_RUNNING = "TimerIsRunning";


class Timer : public virtual Object {
public:
	Timer();
	virtual ~Timer();

	void startTimer();

	static void processFunc(Object*, float);
};

#endif // OBJECT_TIMER