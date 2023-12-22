#include <ultra64.h>
#include "game/object_helpers.h"
#include "engine/math_util.h"
#include "behavior_data.h"
#include "actors/circlepiececol/collision_header.h"

#define LAYER_DENSITY 1600
#define LAYER_COUNT 20

#define BP_FINISH 0x26
#define BP_NORMAL 0x00
#define BP_HASLAVA 0x01
#define BP_BREAK 0x02

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

		int i;
		for (i = 0; i < endcount; i++) {
			struct Object *oc = spawn_object_relative(bp, 0, yPos, 0, o, MODEL_SLICE, behavs[1]);
			oc->oMoveAngleYaw = baseYaw + (D_ANGLE * i);
			oc->oFaceAngleYaw = baseYaw + (D_ANGLE * i);
			if (bp == 0x26) {
				oc->oAnimState = 2;
				obj_set_collision_data(oc, circlepiececol_FINISH);
			} else if (random_float() < 0.1f) {
				oc->oAnimState = 1;
				obj_set_collision_data(oc, circlepiececol_lava);
			} else {
				oc->oAnimState = 0;
				obj_set_collision_data(oc, circlepiececol_collision);
			}
			vec3f_set_dist_and_angle(z, &oc->oPosVec, 800, 0, baseYaw + (D_ANGLE * i) + 0x4000);
		}


		#define ANGLE_CENTER 0x80
		struct Object *oc = spawn_object_relative(bp, 0, yPos, 0, o, MODEL_SLICE, behavs[0]);
		oc->oMoveAngleYaw = baseYaw + ANGLE_CENTER + (D_ANGLE * endcount);
		oc->oFaceAngleYaw = baseYaw + ANGLE_CENTER + (D_ANGLE * endcount);
		oc->oAnimState = 3;
		obj_set_collision_data(oc, circlepiececol_collision);
		vec3f_set_dist_and_angle(z, &oc->oPosVec, 800, 0, baseYaw + ANGLE_CENTER + (D_ANGLE * endcount) + 0x4000);

		baseYaw += 0x1000 * (random_float() < 0.5f ? 4 : 1) * random_sign();
	}

	osSyncPrintf("LAST J %f", o->oPosY + (j * LAYER_DENSITY));

	mark_obj_for_deletion(o);
}
void bhv_layerSpawner_loop(void) {
	
}
