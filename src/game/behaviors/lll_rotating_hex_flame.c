#include <ultra64.h>
#include "behavior_data.h"
#include "global_object_fields.h"
#include "engine/surface_load.h"
#include "game/object_helpers.h"

/* Lll Rotating Hex Flame */
#define /*0x0F4*/ O_LLL_ROTATING_HEX_FLAME_RELATIVE_POS_INDEX   0x1B
#define /*0x0F4*/ O_LLL_ROTATING_HEX_FLAME_RELATIVE_POS_X_INDEX (O_LLL_ROTATING_HEX_FLAME_RELATIVE_POS_INDEX + 0) // 0x1B
#define /*0x0F8*/ O_LLL_ROTATING_HEX_FLAME_RELATIVE_POS_Y_INDEX (O_LLL_ROTATING_HEX_FLAME_RELATIVE_POS_INDEX + 1) // 0x1C
#define /*0x0FC*/ O_LLL_ROTATING_HEX_FLAME_RELATIVE_POS_Z_INDEX (O_LLL_ROTATING_HEX_FLAME_RELATIVE_POS_INDEX + 2) // 0x1D
#define /*0x0F4*/ oLllRotatingHexFlameRelativePosVec            OBJECT_FIELD_F32(O_LLL_ROTATING_HEX_FLAME_RELATIVE_POS_INDEX)
#define /*0x0F4*/ oLllRotatingHexFlameRelativePosX              OBJECT_FIELD_F32(O_LLL_ROTATING_HEX_FLAME_RELATIVE_POS_X_INDEX)
#define /*0x0F8*/ oLllRotatingHexFlameRelativePosY              OBJECT_FIELD_F32(O_LLL_ROTATING_HEX_FLAME_RELATIVE_POS_Y_INDEX)
#define /*0x0FC*/ oLllRotatingHexFlameRelativePosZ              OBJECT_FIELD_F32(O_LLL_ROTATING_HEX_FLAME_RELATIVE_POS_Z_INDEX)

void bhv_lll_rotating_hex_flame_loop(void) {
    cur_obj_set_pos_relative(o->parentObj, o->oLllRotatingHexFlameRelativePosX, o->oLllRotatingHexFlameRelativePosY, o->oLllRotatingHexFlameRelativePosZ);

    o->oPosY = o->parentObj->oPosY + 100.0f;

    if (o->parentObj->oAction == LLL_FIRE_BAR_ACT_REMOVE_FLAMES) {
        obj_mark_for_deletion(o);
    }
}

void fire_bar_spawn_flames(s16 yaw) {
    struct Object *flameObj;
    s32 i;
    f32 xOffset = sins(yaw) * 200.0f;
    f32 zOffset = coss(yaw) * 200.0f;
    s32 amt = o->oBehParams2ndByte; // Amount of flames to spawn

    // Use the vanilla default value if the bparam is 0
    if (amt == 0) {
        amt = 4;
    }

    for (i = 0; i < amt; i++) {
        flameObj = spawn_object(o, MODEL_RED_FLAME, bhvLllRotatingHexFlame);
        flameObj->oLllRotatingHexFlameRelativePosX += xOffset;
        flameObj->oLllRotatingHexFlameRelativePosY = o->oPosY - 200.0f;
        flameObj->oLllRotatingHexFlameRelativePosZ += zOffset;
        obj_scale(flameObj, 6.0f);
        xOffset += sins(yaw) * 150.0f;
        zOffset += coss(yaw) * 150.0f;
    }
}

void fire_bar_act_inactive(void) {
    if (o->oDistanceToMario < o->oDrawingDistance) {
        o->oAction = LLL_FIRE_BAR_ACT_SPAWN_FLAMES;
    }
}

void fire_bar_act_spawn_flames(void) {
    fire_bar_spawn_flames(0);
    fire_bar_spawn_flames(-0x8000);
    o->oAngleVelYaw = 0;
    o->oMoveAngleYaw = 0;
    o->oAction = LLL_FIRE_BAR_ACT_ACTIVE;
}

void fire_bar_act_active(void) {
    o->oAngleVelYaw = -0x100;
    o->oMoveAngleYaw += o->oAngleVelYaw;
    if (o->oDistanceToMario > o->oDrawingDistance + 200.0f) {
        o->oAction = LLL_FIRE_BAR_ACT_REMOVE_FLAMES;
    }
}

void fire_bar_act_remove_flames(void) {
    o->oAction = LLL_FIRE_BAR_ACT_INACTIVE;
}

ObjActionFunc sRotatingCwFireBarsActions[] = {
    fire_bar_act_inactive,
    fire_bar_act_spawn_flames,
    fire_bar_act_active,
    fire_bar_act_remove_flames,
};

void bhv_lll_rotating_block_fire_bars_loop(void) {
    cur_obj_call_action_function(sRotatingCwFireBarsActions);
    load_object_collision_model();
}
