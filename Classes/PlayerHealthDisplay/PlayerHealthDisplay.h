#ifndef OBJECT_PLAYER_HEALTH_DISPLAY
#define OBJECT_PLAYER_HEALTH_DISPLAY

#include "../HealthDisplayAbstract/HealthDisplayAbstract.h"

#include <string>

const auto OBJECT_CLASS_PLAYER_HEALTH_DISPLAY = "PlayerHealthDisplay";

class PlayerHealthDisplay : public virtual HealthDisplayAbstract {
private:
	std::unordered_map <std::string, Object*>* objectsContainerPtr;
public:
	PlayerHealthDisplay();
	virtual ~PlayerHealthDisplay();


	static void process_func(Object* selfptr, float delta);

	// helper variables
private:
	std::string playerId;

};


#endif