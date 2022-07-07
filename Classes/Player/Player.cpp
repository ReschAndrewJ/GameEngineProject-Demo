#include "Player.h"

#include "../../General/CollisionMaskEnums.h"
#include "../../General/ViewEnums.h"
#include "../../General/KeysToPoll.h"
#include "../Stage/Stage.h"

Player::Player() {
	addClassIdentifier(OBJECT_CLASS_PLAYER);

	setAttribute(ATTRIBUTE_COLLIDER_MASK_OWN, (int)Collision_Masks::PLAYER);
	setAttribute(ATTRIBUTE_COLLIDER_MASK_TARGET, 
		(int)Collision_Masks::BOUNDARY | (int)Collision_Masks::BULLET_ENEMY);
	
	addAfterCreationFunction(&afterCreationFunc);
	addProcessFunction(&processFunc, 5);
	addRequestedPointer(PTR_IDENTIFIER::INPUT_HANDLER_PTR, &inputHandlerPtr);
}
Player::~Player() {}


void Player::processFunc(Object* selfptr, float delta) {
	dynamic_cast<Player*>(selfptr)->doAttacks();
}


void Player::getMovementDirection(float move[3]) const {
	float movX = 0;
	float movY = 0;
	float movZ = 0;

	bool keyW = inputHandlerPtr->getKeyState(keys::W, input_states::PRESSED);
	bool keyA = inputHandlerPtr->getKeyState(keys::A, input_states::PRESSED);
	bool keyS = inputHandlerPtr->getKeyState(keys::S, input_states::PRESSED);
	bool keyD = inputHandlerPtr->getKeyState(keys::D, input_states::PRESSED);

	Object* stagePtr = getObject(getParentIdentifier());
	while (stagePtr != nullptr && !stagePtr->is_class(OBJECT_CLASS_STAGE)) {
		stagePtr = getObject(stagePtr->getParentIdentifier());
	}
	int view = stagePtr == nullptr ? (int)VIEWS::FROM_TOP : (int)stagePtr->getAttribute(ATTRIBUTE_STAGE_VIEW);
	if (view == (int)VIEWS::FROM_TOP) {
		if (keyW) movZ -= 1;
		if (keyS) movZ += 1;
		if (keyA) movX -= 1;
		if (keyD) movX += 1;
	}
	if (view == (int)VIEWS::FROM_BACK) {
		if (keyW) movY -= 1;
		if (keyS) movY += 1;
		if (keyA) movX -= 1;
		if (keyD) movX += 1;
	} 
	if (view == (int)VIEWS::FROM_SIDE) {
		if (keyW) movY -= 1;
		if (keyS) movY += 1;
		if (keyA) movZ += 1;
		if (keyD) movZ -= 1;
	}

	move[0] = movX;
	move[1] = movY;
	move[2] = movZ;
}


void Player::doAttacks() {}