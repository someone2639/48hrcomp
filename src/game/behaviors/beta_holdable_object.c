#include <ultra64.h>
#include "global_object_fields.h"
#include "game/object_helpers.h"

/**
 * Behavior for bhvBetaHoldableObject.
 * This is a simple implementation of a holdable object, probably used
 * for testing. This was previously assumed to be a beta shell, as there
 * are unused shell models left in the game; however, there is no evidence
 * to support this theory.
 */

/**
 * Initialization function for bhvBetaHoldableObject.
 * Just sets various physics constants for the object.
 */
void bhv_beta_holdable_object_init(void) {
    o->oGravity = 2.5f;
    o->oFriction = 0.8f;
    o->oBuoyancy = 1.3f;
}

/**
 * Drop the object.
 */
static void beta_holdable_object_drop(void) {
    // Re-enable rendering
    cur_obj_enable_rendering();

    cur_obj_get_dropped();

    o->oHeldState = HELD_FREE;

    o->oForwardVel = 0.0f;
    o->oVelY = 0.0f;
}

/**
 * Throw the object.
 */
static void beta_holdable_object_throw(void) {
    cur_obj_enable_rendering();

    o->oHeldState = HELD_FREE;

    // This flag is never set, why is it cleared?
    o->oFlags &= ~OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW;

    // Set initial velocity
    o->oForwardVel = 40.0f;
    o->oVelY = 20.0f;
}

/**
 * Update function for bhvBetaHoldableObject.
 * Apply standard physics to the object if not held;
 * otherwise, handle holding logic.
 */
void bhv_beta_holdable_object_loop(void) {
    switch (o->oHeldState) {
        case HELD_FREE:
            // Apply standard physics
            object_step();
            break;

        case HELD_HELD:
            // Disable rendering to hide the object while it's held
            cur_obj_disable_rendering();
            break;

        case HELD_THROWN:
            beta_holdable_object_throw();
            break;

        case HELD_DROPPED:
            beta_holdable_object_drop();
            break;
    }
}
