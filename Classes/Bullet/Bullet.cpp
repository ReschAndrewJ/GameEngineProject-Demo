#include "Bullet.h"


Bullet::Bullet() {
	addClassIdentifier(OBJECT_CLASS_BULLET);

	createAttribute(ATTRIBUTE_BULLET_DAMAGE, Attribute::types::INTEGER);
	createAttribute(ATTRIBUTE_BULLET_ITIME, Attribute::types::DOUBLE);
}
Bullet::~Bullet() { queueDestroyObject(getIdentifier()); }
