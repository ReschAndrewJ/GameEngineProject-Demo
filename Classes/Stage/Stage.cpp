#include "Stage.h"
#include "../../General/ViewEnums.h"

Stage::Stage() {
	addClassIdentifier(OBJECT_CLASS_STAGE);

	createAttribute(ATTRIBUTE_STAGE_NEXT_FILEPATH, Attribute::types::STRING);
	createAttribute(ATTRIBUTE_STAGE_NEXT_IDENTIFIER, Attribute::types::STRING);
	createAttribute(ATTRIBUTE_STAGE_COMPLETE, Attribute::types::BOOLEAN);

	createAttribute(ATTRIBUTE_STAGE_VIEW, Attribute::types::INTEGER);
	setAttribute(ATTRIBUTE_STAGE_VIEW, (int)VIEWS::FROM_TOP);
}
Stage::~Stage() {}


