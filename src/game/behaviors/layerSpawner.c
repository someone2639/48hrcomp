#include <ultra64.h>
#include "game/object_helpers.h"
#include "engine/math_util.h"
#include "behavior_data.h"

void bhv_layerSpawner_init(void) {
	// u8 *behavs[] = {

	// };

	for (int i = 0; i < 6; i++) {
		struct Object *oc = spawn_object_relative(0, 0, 0, 0, o, MODEL_SLICE, bhvBreakableBox);
		oc->oFaceAngleYaw = 0x1700 * i;
	}
}
void bhv_layerSpawner_loop(void) {
	
}
