#include "Player_TypeA.h"

#include "../TypeABullet/TypeABullet.h" // ATTACK OBJECT CLASS
#include "../../General/KeysToPoll.h"
#include "../SingleCallSound/SingleCallSound.h"
#include "../../General/CollisionMaskEnums.h"

Player_TypeA::Player_TypeA() {
	addClassIdentifier(OBJECT_CLASS_PLAYER_TYPE_A);

	createAttribute(ATTRIBUTE_PLAYER_TYPE_A_BULLET_FILEPATH, Attribute::types::STRING);
	createAttribute(ATTRIBUTE_PLAYER_TYPE_A_BULLET_IDENTIFIER, Attribute::types::STRING);

	createAttribute(ATTRIBUTE_PLAYER_TYPE_A_BULLET_COOLDOWN, Attribute::types::DOUBLE);
	createAttribute(ATTRIBUTE_PLAYER_TYPE_A_COOLDOWN_REMAINING, Attribute::types::DOUBLE);
	createAttribute(ATTRIBUTE_PLAYER_TYPE_A_BULLET_FIRE_SOUND, Attribute::types::STRING);

	addRequestedPointer(PTR_IDENTIFIER::INPUT_HANDLER_PTR, &inputHandlerPtr);

	addProcessFunction(&processFunc, 6);
}
Player_TypeA::~Player_TypeA() {}


void Player_TypeA::processFunc(Object* selfptr, float delta) {
	selfptr->setAttribute(ATTRIBUTE_PLAYER_TYPE_A_COOLDOWN_REMAINING,
		(float)selfptr->getAttribute(ATTRIBUTE_PLAYER_TYPE_A_COOLDOWN_REMAINING) - delta > 0 ?
		(float)selfptr->getAttribute(ATTRIBUTE_PLAYER_TYPE_A_COOLDOWN_REMAINING) - delta : 0);
}


void Player_TypeA::doAttacks() {
	if ((inputHandlerPtr->getKeyState(keys::Space, input_states::PRESSED)
		|| inputHandlerPtr->getKeyState(keys::Enter, input_states::PRESSED)) &&
		(float)getAttribute(ATTRIBUTE_PLAYER_TYPE_A_COOLDOWN_REMAINING) == 0) {
		queueCreateObject(getAttribute(ATTRIBUTE_PLAYER_TYPE_A_BULLET_FILEPATH),
			getAttribute(ATTRIBUTE_PLAYER_TYPE_A_BULLET_IDENTIFIER), getParentIdentifier(), {
				{ATTRIBUTE_SPATIAL_POSITION_X, getAttribute(ATTRIBUTE_SPATIAL_POSITION_X)},
				{ATTRIBUTE_SPATIAL_POSITION_Y, getAttribute(ATTRIBUTE_SPATIAL_POSITION_Y)},
				{ATTRIBUTE_SPATIAL_POSITION_Z, (float)getAttribute(ATTRIBUTE_SPATIAL_POSITION_Z) - 40},
				{ATTRIBUTE_COLLIDER_MASK_OWN, (int)Collision_Masks::BULLET_PLAYER}
			});
		queueCreateObject("Resources/InstanceFiles/EmptyInsts.inst",
			"SingleCallSound", getParentIdentifier(),
			{ {ATTRIBUTE_SOUND_FILE, getAttribute(ATTRIBUTE_PLAYER_TYPE_A_BULLET_FIRE_SOUND)},
			{ ATTRIBUTE_SOUND_VOLUME, 10 } });
		setAttribute(ATTRIBUTE_PLAYER_TYPE_A_COOLDOWN_REMAINING,
			getAttribute(ATTRIBUTE_PLAYER_TYPE_A_BULLET_COOLDOWN));
	}
	
}

