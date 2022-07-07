#ifndef OBJECT_ENEMY
#define OBJECT_ENEMY

#include "../LiveEntity/LiveEntity.h"

const auto OBJECT_CLASS_ENEMY = "Enemy";

class Enemy : public virtual LiveEntity {
public:
	Enemy();
	virtual ~Enemy();

protected:
	// should return the direction vector for the enemy's movement that frame
	virtual void getMovementDirection(float movementSlope[3]) const override = 0;

};


#endif // OBJECT_ENEMY