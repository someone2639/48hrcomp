#include <ultra64.h>
#include "behavior_data.h"
#include "global_object_fields.h"
#include "game/object_helpers.h"

// TODO: Is this really "mist"?

void bhv_water_mist_spawn_loop(void) {
    clear_particle_flags(ACTIVE_PARTICLE_BREATH);
    spawn_object(o, MODEL_MIST, bhvWaterMist);
}

void bhv_water_mist_loop(void) {
    f32 scale;

    if (o->oTimer == 0) {
        o->oMoveAngleYaw = gMarioObject->oMoveAngleYaw;
        obj_translate_xz_random(o, 10.0f);
    }

    cur_obj_move_using_fvel_and_gravity();
    o->oOpacity -= 42;
    scale = (254 - o->oOpacity) / 254.0f * 1.0f + 0.5f; // seen this before
    cur_obj_scale(scale);

    if (o->oOpacity < 2) {
        obj_mark_for_deletion(o);
    }
}
