#include <ultra64.h>
#include "behavior_data.h"
#include "global_object_fields.h"
#include "engine/surface_collision.h"
#include "game/interaction.h"
#include "game/object_helpers.h"
#include "game/spawn_sound.h"

/* Sushi Shark */
#define /*0x0F4*/ oSushiSharkAngleFromHome OBJECT_FIELD_S32(0x1B)

void bhv_sushi_shark_loop(void) {
    f32 waterLevel = find_water_level(o->oPosX, o->oPosZ);

    o->oPosX = o->oHomeX + sins(o->oSushiSharkAngleFromHome) * 1700.0f;
    o->oPosZ = o->oHomeZ + coss(o->oSushiSharkAngleFromHome) * 1700.0f;
    o->oPosY = waterLevel + o->oHomeY + sins(o->oSushiSharkAngleFromHome) * 200.0f;

    o->oMoveAngleYaw = o->oSushiSharkAngleFromHome + 0x4000;
    o->oSushiSharkAngleFromHome += 0x80;

    if (gMarioObject->oPosY - waterLevel > -500.0f) {
        if (o->oPosY - waterLevel > -200.0f) {
            spawn_object_with_scale(o, MODEL_WAVE_TRAIL, bhvObjectWaveTrail, 4.0f);
        }
    }
    if (!(o->oTimer & 0x0F)) {
        cur_obj_play_sound_2(SOUND_OBJ_SUSHI_SHARK_WATER_SOUND);
    }

    o->oInteractStatus = INT_STATUS_NONE;
}
