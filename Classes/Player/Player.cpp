#include "Player.h"

#include "../../General/CollisionMaskEnums.h"
#include "../../General/ViewEnums.h"
#include "../../General/KeysToPoll.h"
#include "../Stage/Stage.h"

#include "../SingleCallSound/SingleCallSound.h"

#include "../StageControl/StageControl.h"

Player::Player() {
	addClassIdentifier(OBJECT_CLASS_PLAYER);

	setAttribute(ATTRIBUTE_COLLIDER_MASK_OWN,
		(int)getAttribute(ATTRIBUTE_COLLIDER_MASK_OWN) | (int)Collision_Masks::PLAYER);
	setAttribute(ATTRIBUTE_COLLIDER_MASK_TARGET, 
		(int)getAttribute(ATTRIBUTE_COLLIDER_MASK_TARGET) |
		(int)Collision_Masks::BOUNDARY | (int)Collision_Masks::BULLET_ENEMY);
	
	createAttribute(ATTRIBUTE_PLAYER_DAMAGE_SOUND, Attribute::types::STRING);

	addProcessFunction(&processFunc, 5);
	addRequestedPointer(PTR_IDENTIFIER::INPUT_HANDLER_PTR, &inputHandlerPtr);
}
Player::~Player() {}


void Player::processFunc(Object* selfptr, float delta) {
	if (selfptr->getObject(selfptr->getParentIdentifier()) != nullptr &&
		selfptr->getObject(selfptr->getParentIdentifier())->is_class(OBJECT_CLASS_STAGE_CONTROL)) {
		selfptr->setAttribute(ATTRIBUTE_SPATIAL_POSITION_X, 99999);
	}
	
	dynamic_cast<Player*>(selfptr)->doAttacks();
}


void Player::getMovementDirection(float move[3]) const {
	float movX = 0;
	float movY = 0;
	float movZ = 0;

	bool keyW = inputHandlerPtr->getKeyState(keys::W, input_states::PRESSED)
		|| inputHandlerPtr->getKeyState(keys::Up, input_states::PRESSED);
	bool keyA = inputHandlerPtr->getKeyState(keys::A, input_states::PRESSED)
		|| inputHandlerPtr->getKeyState(keys::Left, input_states::PRESSED);
	bool keyS = inputHandlerPtr->getKeyState(keys::S, input_states::PRESSED)
		|| inputHandlerPtr->getKeyState(keys::Down, input_states::PRESSED);
	bool keyD = inputHandlerPtr->getKeyState(keys::D, input_states::PRESSED)
		|| inputHandlerPtr->getKeyState(keys::Right, input_states::PRESSED);

	Object* stagePtr = getObject(getParentIdentifier());
	while (stagePtr != nullptr && !stagePtr->is_class(OBJECT_CLASS_STAGE)) {
		stagePtr = getObject(stagePtr->getParentIdentifier());
	}
	int view = stagePtr == nullptr ? (int)VIEWS::FROM_TOP : (int)stagePtr->getAttribute(ATTRIBUTE_STAGE_VIEW);
	switch (view)
	{
	case (int)VIEWS::FROM_TOP:
		if (keyW) movZ -= 1; if (keyS) movZ += 1;
		if (keyA) movX -= 1; if (keyD) movX += 1;
		break;
	case (int)VIEWS::FROM_BACK:
		if (keyW) movY -= 1; if (keyS) movY += 1;
		if (keyA) movX -= 1; if (keyD) movX += 1;
		break;
	case (int)VIEWS::FROM_SIDE:
		if (keyW) movY -= 1; if (keyS) movY += 1;
		if (keyA) movZ += 1; if (keyD) movZ -= 1;
		break;
	default:
		if (keyW) movZ -= 1; if (keyS) movZ += 1;
		if (keyA) movX -= 1; if (keyD) movX += 1;
		break;
	}

	move[0] = movX;
	move[1] = movY;
	move[2] = movZ;
}


void Player::onDamage() {
	queueCreateObject("Resources/InstanceFiles/EmptyInsts.inst", "SingleCallSound", getParentIdentifier(),
		{ {ATTRIBUTE_SOUND_FILE, getAttribute(ATTRIBUTE_PLAYER_DAMAGE_SOUND)},
		{ATTRIBUTE_SOUND_VOLUME, 50} }
	);
}

void Player::doAttacks() {}


void Player::onDeath() {
	Object* parent = getObject(getParentIdentifier());
	while (parent != nullptr && !parent->is_class(OBJECT_CLASS_STAGE_CONTROL)) {
		parent = getObject(parent->getParentIdentifier());
	}
	if (parent != nullptr)
		parent->setAttribute(ATTRIBUTE_STAGE_CONTROL_TRANSITION_STATE, STAGE_TRANSITION_ENDSTAGE);
}