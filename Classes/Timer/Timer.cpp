#include "Timer.h"

Timer::Timer() {
	addClassIdentifier(OBJECT_CLASS_TIMER);

	createAttribute(ATTRIBUTE_TIMER_LENGTH, Attribute::types::DOUBLE);
	createAttribute(ATTRIBUTE_TIMER_OFFSET, Attribute::types::DOUBLE);
	createAttribute(ATTRIBUTE_TIMER_TIMEOUT, Attribute::types::BOOLEAN);
	createAttribute(ATTRIBUTE_TIMER_LOOP, Attribute::types::BOOLEAN);
	createAttribute(ATTRIBUTE_TIMER_RUNNING, Attribute::types::BOOLEAN);

	addProcessFunction(&processFunc, 1);
}
Timer::~Timer() {}

void Timer::processFunc(Object* selfptr, float delta) {
	selfptr->setAttribute(ATTRIBUTE_TIMER_TIMEOUT, false);
	if (!(bool)selfptr->getAttribute(ATTRIBUTE_TIMER_RUNNING)) return;

	float offset = selfptr->getAttribute(ATTRIBUTE_TIMER_OFFSET);
	offset += delta;

	if (offset >= (float)selfptr->getAttribute(ATTRIBUTE_TIMER_LENGTH)) {

		selfptr->setAttribute(ATTRIBUTE_TIMER_TIMEOUT, true);
		selfptr->setAttribute(ATTRIBUTE_TIMER_RUNNING, false);
		if ((bool)selfptr->getAttribute(ATTRIBUTE_TIMER_LOOP)) {
			offset = 0;
			dynamic_cast<Timer*>(selfptr)->startTimer();
			return;
		}
	}
	selfptr->setAttribute(ATTRIBUTE_TIMER_OFFSET, offset);
}

void Timer::startTimer() {
	setAttribute(ATTRIBUTE_TIMER_OFFSET, 0);
	setAttribute(ATTRIBUTE_TIMER_RUNNING, true);
}