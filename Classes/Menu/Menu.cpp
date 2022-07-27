#include "Menu.h"

#include "../../General/KeysToPoll.h"
#include "../GameContainer/GameContainer.h"
#include "../../_GameEngineSrc/Objects/SoundOutput/Object_SoundOutput.h"

Menu::Menu() {
	addClassIdentifier(OBJECT_CLASS_MENU);

	addProcessFunction(&process_func, 10);
	addRequestedPointer(PTR_IDENTIFIER::INPUT_HANDLER_PTR, &inputHandlerPtr);
}
Menu::~Menu() {}



void Menu::process_func(Object* selfptr, float delta) {
	Menu* self = dynamic_cast<Menu*>(selfptr);
	for (const auto& childId : selfptr->getObject(selfptr->getParentIdentifier())->getChildrenIdentifiers()) {
		if (selfptr->getObject(childId)->is_class(OBJECT_CLASS_GAME_CONTAINER)) {
			return;
		}
	}
	if ((float)selfptr->getAttribute(ATTRIBUTE_SPATIAL_POSITION_X) != 0) {
		self->menuJustAppeared = true;
		selfptr->setAttribute(ATTRIBUTE_SPATIAL_POSITION_X, 0);
		
	}
	if (self->menuJustAppeared) for (const auto& child : selfptr->getChildrenIdentifiers()) {
		if (selfptr->getObject(child)->is_class(OBJECT_CLASS_SOUNDOUTPUT)) {
			dynamic_cast<Object_SoundOutput*>(selfptr->getObject(child))->play();
		}
	}
	self->menuJustAppeared = false;

	bool start = self->inputHandlerPtr->getKeyState(keys::Enter, input_states::JUST_PRESSED);

	if (start) {
		selfptr->setAttribute(ATTRIBUTE_SPATIAL_POSITION_X, INFINITY);
		for (const auto& child : self->getChildrenIdentifiers()) {
			if (self->getObject(child)->is_class(OBJECT_CLASS_SOUNDOUTPUT)) {
				dynamic_cast<Object_SoundOutput*>(self->getObject(child))->stop();
			}
		}
		self->queueCreateObject(
			"Resources/InstanceFiles/Main.inst", "Game", self->getParentIdentifier(), {}
		);
	}
	else if (self->inputHandlerPtr->getKeyState(keys::Grave, input_states::JUST_PRESSED)) {
		selfptr->setAttribute(ATTRIBUTE_SPATIAL_POSITION_X, INFINITY);
		for (const auto& child : self->getChildrenIdentifiers()) {
			if (self->getObject(child)->is_class(OBJECT_CLASS_SOUNDOUTPUT)) {
				dynamic_cast<Object_SoundOutput*>(self->getObject(child))->stop();
			}
		}
		self->queueCreateObject(
			"Resources/InstanceFiles/Main.inst", "SkipToBoss", self->getParentIdentifier(), {
			}
		);
	}
	else if (self->inputHandlerPtr->getKeyState(keys::C, input_states::JUST_PRESSED)) {
		selfptr->setAttribute(ATTRIBUTE_SPATIAL_POSITION_X, INFINITY);
		for (const auto& child : self->getChildrenIdentifiers()) {
			if (self->getObject(child)->is_class(OBJECT_CLASS_SOUNDOUTPUT)) {
				dynamic_cast<Object_SoundOutput*>(self->getObject(child))->stop();
			}
		}
		self->queueCreateObject(
			"Resources/InstanceFiles/Main.inst", "SkipToCredits", self->getParentIdentifier(), {
			}
		);
	}

}
