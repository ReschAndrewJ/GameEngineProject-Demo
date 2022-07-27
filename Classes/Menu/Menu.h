#ifndef OBJECT_MENU
#define OBJECT_MENU

#include "../../_GameEngineSrc/Objects/Spatial/Object_Spatial.h"

#include "../../_GameEngineSrc/Engines/Main/Input_Handler.h"

const auto OBJECT_CLASS_MENU = "Menu";

class Menu : public virtual Object_Spatial {
private:
	Input_Handler* inputHandlerPtr;
public:
	Menu();
	virtual ~Menu();


	static void process_func(Object*, float);

	// helper variables
private:
	bool menuJustAppeared = true;

};


#endif