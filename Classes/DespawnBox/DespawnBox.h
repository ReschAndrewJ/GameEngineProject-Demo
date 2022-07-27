#ifndef OBJECT_DESPWN_BOX
#define OBJECT_DESPAWN_BOX

#include "../../_GameEngineSrc/Objects/Spatial/Object_Spatial.h"

const auto OBJECT_CLASS_DESPAWN_BOX = "DespawnBox";

class DespawnBox : public virtual Object_Spatial {
public:
	DespawnBox();
	virtual ~DespawnBox();

	static void process_func(Object*, float);
};


#endif