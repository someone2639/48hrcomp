#include <ultra64.h>
#include "behavior_data.h"
#include "global_object_fields.h"
#include "engine/math_util.h"
#include "game/interaction.h"
#include "game/object_helpers.h"
#include "game/spawn_sound.h"

/* Ship Part 3 */
#define /*0x0F4*/ oShipPart3LoopPitch OBJECT_FIELD_S32(0x1B)
#define /*0x0F8*/ oShipPart3LoopRoll  OBJECT_FIELD_S32(0x1C)

/* Jrb Sliding Box */
#define /*0x0F4*/ oJrbSlidingBoxShipObj   OBJECT_FIELD_OBJ(0x1B)
#define /*0x0F8*/ oJrbSlidingBoxAngle     OBJECT_FIELD_S32(0x1C)
#define /*0x0FC*/ oJrbSlidingBoxAdditiveZ OBJECT_FIELD_F32(0x1D)

struct ObjectHitbox sSkullSlidingBoxHitbox = {
    /* interactType:      */ INTERACT_DAMAGE,
    /* downOffset:        */ 0,
    /* damageOrCoinValue: */ 1,
    /* health:            */ 1,
    /* numLootCoins:      */ 0,
    /* radius:            */ 130,
    /* height:            */ 100,
    /* hurtboxRadius:     */ 0,
    /* hurtboxHeight:     */ 0,
};

void bhv_sunken_ship_part_loop(void) {
    if (o->oDistanceToMario > 10000.0f) {
        o->oOpacity = 140;
    } else {
        o->oOpacity = o->oDistanceToMario * 140.0f / 10000.0f;
    }

    cur_obj_disable_rendering();
}

void bhv_ship_part_3_loop(void) {
    s16 initialPitch = o->oFaceAnglePitch;
    s16 initialRoll = o->oFaceAngleRoll;

    cur_obj_set_pos_to_home_with_debug();

    o->oShipPart3LoopPitch += 0x100;

    o->oFaceAnglePitch = sins(o->oShipPart3LoopPitch) * 0x400;
    o->oFaceAngleRoll = sins(o->oShipPart3LoopRoll ) * 0x400;
    o->oAngleVelPitch = o->oFaceAnglePitch - initialPitch;
    o->oAngleVelRoll = o->oFaceAngleRoll  - initialRoll;

    if (gMarioObject->oPosY > 1000.0f) {
        cur_obj_play_sound_1(SOUND_ENV_BOAT_ROCKING1);
    }
}

void bhv_jrb_sliding_box_loop(void) {
    Mat4 mtx;
    Vec3f shipToBoxPos1;
    Vec3f shipToBoxPos2;
    Vec3s shipRotation;
    struct Object *shipObj;
    if (o->oJrbSlidingBoxShipObj == NULL) {
        shipObj = cur_obj_nearest_object_with_behavior(bhvInSunkenShip3);

        if (shipObj != NULL) {
            o->oJrbSlidingBoxShipObj = shipObj;
            vec3f_diff(&o->oParentRelativePosVec, &o->oPosVec, &shipObj->oPosVec);
        }
    } else {
        shipObj = o->oJrbSlidingBoxShipObj;
        vec3i_to_vec3s(shipRotation, &shipObj->oFaceAngleVec);
        vec3f_copy(shipToBoxPos1, &o->oParentRelativePosVec);
        mtxf_rotate_zxy_and_translate(mtx, shipToBoxPos1, shipRotation);
        linear_mtxf_mul_vec3f(mtx, shipToBoxPos2, shipToBoxPos1);
        vec3f_sum(&o->oPosVec, &shipObj->oPosVec, shipToBoxPos2);
        o->oFaceAnglePitch = shipObj->oFaceAnglePitch;
    }

    o->oJrbSlidingBoxAdditiveZ = sins(o->oJrbSlidingBoxAngle) * 20.0f;
    o->oJrbSlidingBoxAngle += 0x100;
    o->oParentRelativePosZ += o->oJrbSlidingBoxAdditiveZ;

    if (gMarioObject->oPosY > 1000.0f && absf(o->oJrbSlidingBoxAdditiveZ) > 3.0f) {
        cur_obj_play_sound_1(SOUND_AIR_ROUGH_SLIDE);
    }

    obj_set_hitbox(o, &sSkullSlidingBoxHitbox);

    if (!(o->oJrbSlidingBoxAngle & 0x7FFF)) {
        cur_obj_become_tangible();
    }

    if (obj_check_if_collided_with_object(o, gMarioObject)) {
        o->oInteractStatus = INT_STATUS_NONE;
        cur_obj_become_intangible();
    }
}
