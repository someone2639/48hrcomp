#include <ultra64.h>
#include "global_object_fields.h"
#include "engine/surface_load.h"
#include "game/object_helpers.h"
#include "game/save_file.h"

// moat_grill.inc.c

void bhv_moat_grills_loop(void) {
    if (save_file_get_flags() & SAVE_FLAG_MOAT_DRAINED) {
        cur_obj_set_model(MODEL_NONE);
    } else {
        load_object_collision_model();
    }
}
