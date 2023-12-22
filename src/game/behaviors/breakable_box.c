#include <ultra64.h>
#include "behavior_data.h"
#include "global_object_fields.h"
#include "engine/surface_load.h"
#include "game/interaction.h"
#include "game/object_helpers.h"
#include "game/spawn_sound.h"
#include "levels/wdw/header.h"

struct ObjectHitbox sBreakableBoxHitbox = {
    /* interactType:      */ INTERACT_BREAKABLE,
    /* downOffset:        */  20,
    /* damageOrCoinValue: */   0,
    /* health:            */   1,
    /* numLootCoins:      */   0,
    /* radius:            */ 150,
    /* height:            */ 200,
    /* hurtboxRadius:     */ 150,
    /* hurtboxHeight:     */ 200,
};

#include "actors/circlepiececol/collision_header.h"

Collision *cdata[] = {
    circlepiececol_collision,
    circlepiececol_lava,
    circlepiececol_FINISH,
};

void breakable_box_init(void) {
    int bp = o->oBehParams2ndByte;

    switch (bp) {
        case 0x26:
            obj_set_collision_data(o, cdata[2]);
        break;
        case 1:
            obj_set_collision_data(o, cdata[1]);
        break;
        default:
            obj_set_collision_data(o, cdata[0]);
        break;
    }

}

void hidden_breakable_box_actions(void) {
    struct Object *switchObj;
    obj_set_hitbox(o, &sBreakableBoxHitbox);
    // cur_obj_set_model(MODEL_BREAKABLE_BOX);
    switch (o->oAction) {
        case BREAKABLE_BOX_ACT_HIDDEN:
            cur_obj_disable_rendering();
            cur_obj_become_intangible();
            if (o->oTimer == 0) {
                breakable_box_init();
            }
            if (o->oHiddenObjectSwitchObj == NULL) {
                o->oHiddenObjectSwitchObj = cur_obj_nearest_object_with_behavior(bhvFloorSwitchHiddenObjects);
            }
            switchObj = o->oHiddenObjectSwitchObj;
            if ((switchObj != NULL) && (switchObj->oAction == PURPLE_SWITCH_ACT_TICKING)) {
                o->oAction = BREAKABLE_BOX_ACT_ACTIVE;
                cur_obj_enable_rendering();
                cur_obj_unhide();
            }
            break;
        case BREAKABLE_BOX_ACT_ACTIVE:
            cur_obj_become_tangible();
            if (cur_obj_wait_then_blink(360, 20)) o->oAction = BREAKABLE_BOX_ACT_HIDDEN;
            if (cur_obj_was_attacked_or_ground_pounded()) {
                spawn_mist_particles();
                spawn_triangle_break_particles(30, MODEL_DIRT_ANIMATION, 3.0f, TINY_DIRT_PARTICLE_ANIM_STATE_YELLOW);
                o->oAction = BREAKABLE_BOX_ACT_BROKEN;
                cur_obj_play_sound_2(SOUND_GENERAL_BREAK_BOX);
            }
            load_object_collision_model();
            break;
        case BREAKABLE_BOX_ACT_BROKEN:
            cur_obj_become_intangible();
            cur_obj_disable_rendering();
            o->oInteractStatus = INT_STATUS_NONE;
            switchObj = o->oHiddenObjectSwitchObj;
            if ((switchObj != NULL) && (switchObj->oAction == PURPLE_SWITCH_ACT_IDLE)) {
                o->oAction = BREAKABLE_BOX_ACT_HIDDEN;
            }
            break;
    }
}

void hidden_unbreakable_box_actions(void) {
    struct Object *switchObj;
    obj_set_collision_data(o, wdw_seg7_collision_hidden_platform);
    switch (o->oAction) {
        case BREAKABLE_BOX_ACT_HIDDEN:
            cur_obj_disable_rendering();
            cur_obj_become_intangible();
            if (o->oHiddenObjectSwitchObj == NULL) {
                o->oHiddenObjectSwitchObj = cur_obj_nearest_object_with_behavior(bhvFloorSwitchHiddenObjects);
            }
            switchObj = o->oHiddenObjectSwitchObj;
            if ((switchObj != NULL) && (switchObj->oAction == PURPLE_SWITCH_ACT_TICKING)) {
                o->oAction = BREAKABLE_BOX_ACT_ACTIVE;
                cur_obj_enable_rendering();
                cur_obj_unhide();
            }
            break;
        case BREAKABLE_BOX_ACT_ACTIVE:
            cur_obj_become_tangible();
            if (cur_obj_wait_then_blink(360, 20)) o->oAction = BREAKABLE_BOX_ACT_HIDDEN;
            load_object_collision_model();
            break;
    }
}

void bhv_hidden_object_loop(void) {
    if (o->oBehParams2ndByte == BREAKABLE_BOX_BP_NO_COINS) {
        hidden_breakable_box_actions();
    } else {
        hidden_unbreakable_box_actions();
    }
}

void bhv_breakable_box_loop(void) {
    obj_set_hitbox(o, &sBreakableBoxHitbox);
    // cur_obj_set_model(MODEL_BREAKABLE_BOX);
    if (o->oTimer == 0) breakable_box_init();
    if (cur_obj_was_attacked_or_ground_pounded()) {
        obj_explode_and_spawn_coins(46.0f, COIN_TYPE_YELLOW);
        create_sound_spawner(SOUND_GENERAL_BREAK_BOX);
    }
}
