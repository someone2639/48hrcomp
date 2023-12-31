#include <ultra64.h>
#include "global_object_fields.h"
#include "game/interaction.h"
#include "game/object_helpers.h"
#include "game/spawn_sound.h"

void bhv_tower_door_loop(void) {
    if (o->oTimer == 0) {
        o->oMoveAngleYaw -= 0x4000;
    }

    if (check_mario_attacking()) {
        obj_explode_and_spawn_coins(80.0f, COIN_TYPE_NONE);
        create_sound_spawner(SOUND_GENERAL_WALL_EXPLOSION);
    }
}
