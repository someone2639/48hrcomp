#include <ultra64.h>
#include "global_object_fields.h"
#include "engine/surface_load.h"
#include "game/object_helpers.h"

void bhv_bowsers_sub_init(void) {
    if (gCurrActNum != 1) {
        obj_mark_for_deletion(o);
    } else {
        load_object_static_model();
    }
}
