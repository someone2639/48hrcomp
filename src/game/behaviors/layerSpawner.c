#include <ultra64.h>
#include "game/object_helpers.h"
#include "engine/math_util.h"
#include "behavior_data.h"

#define LAYER_DENSITY 1600
#define LAYER_COUNT 20

#define BP_FINISH 0x26
#define BP_NORMAL 0x00
#define BP_HASLAVA 0x01

void bhv_layerSpawner_init(void) {
	u8 *behavs[] = {
		bhvBreakableBox,
		bhvStaticSlice,
	};

	#define D_ANGLE 0x1680

	int bp = 0;

	int j;

	s16 baseYaw = 0;
	for (j = 0; j < LAYER_COUNT; j++) {
		Vec3f z = {0,0,0};

		s16 yPos = (j * LAYER_DENSITY);
		int endcount;
		if (j == 0) {
			bp = BP_FINISH;
			endcount = 12;
		} else {
			bp = 0;
			endcount = 10;
		}

		z[1] = o->oPosY + yPos;

		for (int i = 0; i < endcount; i++) {
			struct Object *oc = spawn_object_relative(bp, 0, yPos, 0, o, MODEL_SLICE, behavs[1]);
			oc->oMoveAngleYaw = baseYaw + (D_ANGLE * i);
			oc->oFaceAngleYaw = baseYaw + (D_ANGLE * i);

			vec3f_set_dist_and_angle(z, &oc->oPosVec, 800, 0, baseYaw + (D_ANGLE * i) + 0x4000);
		}
		baseYaw += 0x1000 * (random_float() < 0.5f ? 2 : 1) * random_sign();
	}

	osSyncPrintf("LAST J %f", o->oPosY + (j * LAYER_DENSITY));

	mark_obj_for_deletion(o);
}
void bhv_layerSpawner_loop(void) {
	
}
