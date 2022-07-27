#ifndef HEALTH_DISPLAY_ABSTRACT
#define HEALTH_DISPLAY_ABSTRACT

#include "../../_GameEngineSrc/Objects/Sprite/Object_Sprite.h"

const auto OBJECT_CLASS_HEALTH_DISPLAY_ABSTRACT = "HealthDisplayAbstract";


class HealthDisplayAbstract : public virtual Object_Sprite {
private:
	std::unordered_map <std::string, Object*>* objectsContainerPtr;
public:
	HealthDisplayAbstract();
	virtual ~HealthDisplayAbstract();


};


#endif