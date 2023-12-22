#include <ultra64.h>
#include "game/object_helpers.h"
#include "game/level_update.h"
#include "engine/math_util.h"

void bhv_wCoolball_init(void) {
	
}
void bhv_wCoolball_loop(void) {
	vec3_copy(&o->oPosVec, gMarioState->pos);
}
