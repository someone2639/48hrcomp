#include <ultra64.h>
#include "sm64.h"
#include "behavior_data.h"
#include "model_ids.h"
#include "seq_ids.h"
#include "dialog_ids.h"
#include "segment_symbols.h"
#include "level_commands.h"

#include "game/level_update.h"

#include "levels/scripts.h"

#include "actors/common1.h"
#include "actors/group0.h"

/* Fast64 begin persistent block [includes] */
/* Fast64 end persistent block [includes] */

#include "make_const_nonconst.h"
#include "levels/castle_grounds/header.h"

/* Fast64 begin persistent block [scripts] */
/* Fast64 end persistent block [scripts] */

const LevelScript level_castle_grounds_entry[] = {
	INIT_LEVEL(),
	LOAD_YAY0(0x07, _castle_grounds_segment_7SegmentRomStart, _castle_grounds_segment_7SegmentRomEnd), 
	LOAD_YAY0(0x0A, _water_skybox_yay0SegmentRomStart, _water_skybox_yay0SegmentRomEnd), 
	LOAD_YAY0_TEXTURE(0x09, _outside_yay0SegmentRomStart, _outside_yay0SegmentRomEnd), 
	LOAD_YAY0(0x05, _group10_yay0SegmentRomStart, _group10_yay0SegmentRomEnd), 
	LOAD_RAW(0x0C, _group10_geoSegmentRomStart, _group10_geoSegmentRomEnd), 
	LOAD_YAY0(0x06, _group15_yay0SegmentRomStart, _group15_yay0SegmentRomEnd), 
	LOAD_RAW(0x0D, _group15_geoSegmentRomStart, _group15_geoSegmentRomEnd), 
	LOAD_YAY0(0x08, _common0_yay0SegmentRomStart, _common0_yay0SegmentRomEnd), 
	LOAD_RAW(0x0F, _common0_geoSegmentRomStart, _common0_geoSegmentRomEnd), 
	ALLOC_LEVEL_POOL(),
	MARIO(MODEL_MARIO, 0x00000001, bhvMario), 
	JUMP_LINK(script_func_global_1), 
	JUMP_LINK(script_func_global_11), 
	JUMP_LINK(script_func_global_16), 
	LOAD_MODEL_FROM_GEO(MODEL_LEVEL_GEOMETRY_03, castle_grounds_geo_0006F4), 
	LOAD_MODEL_FROM_GEO(MODEL_CASTLE_GROUNDS_BUBBLY_TREE, bubbly_tree_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_CASTLE_GROUNDS_WARP_PIPE, warp_pipe_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_CASTLE_GROUNDS_CASTLE_DOOR, castle_door_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_CASTLE_GROUNDS_METAL_DOOR, metal_door_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_CASTLE_GROUNDS_VCUTM_GRILL, castle_grounds_geo_00070C), 
	LOAD_MODEL_FROM_GEO(MODEL_CASTLE_GROUNDS_FLAG, castle_grounds_geo_000660), 
	LOAD_MODEL_FROM_GEO(MODEL_CASTLE_GROUNDS_CANNON_GRILL, castle_grounds_geo_000724), 
	LOAD_MODEL_FROM_GEO(MODEL_WBALL, wCoolball_geo), 

	/* Fast64 begin persistent block [level commands] */
	/* Fast64 end persistent block [level commands] */

	AREA(1, castle_grounds_area_1),
		WARP_NODE(0x0A, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0xF0, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0xF1, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		OBJECT(MODEL_WBALL, -218, 29986, 378, 0, 0, 0, 0x00000000, bhvwCoolball),
		OBJECT(MODEL_BREAKABLE_BOX, 236, 29786, -499, 0, 0, 0, 0x00000000, bhvBreakableBox),
		OBJECT(MODEL_BREAKABLE_BOX, -218, 29986, 578, 0, 0, 0, 0x00000000, bhvBreakableBox),
		OBJECT(MODEL_BREAKABLE_BOX, 36, 29786, -499, 0, 0, 0, 0x00000000, bhvBreakableBox),
		OBJECT(MODEL_BREAKABLE_BOX, 36, 29786, -699, 0, 0, 0, 0x00000000, bhvBreakableBox),
		OBJECT(MODEL_BREAKABLE_BOX, 236, 29786, -699, 0, 0, 0, 0x00000000, bhvBreakableBox),
		OBJECT(MODEL_BREAKABLE_BOX, -299, 29786, -280, 0, 0, 0, 0x00000000, bhvBreakableBox),
		OBJECT(MODEL_BREAKABLE_BOX, -499, 29786, -280, 0, 0, 0, 0x00000000, bhvBreakableBox),
		OBJECT(MODEL_BREAKABLE_BOX, -499, 29786, -480, 0, 0, 0, 0x00000000, bhvBreakableBox),
		OBJECT(MODEL_BREAKABLE_BOX, -299, 29786, -480, 0, 0, 0, 0x00000000, bhvBreakableBox),
		OBJECT(MODEL_BREAKABLE_BOX, 236, 28600, -499, 0, 0, 0, 0x00000000, bhvBreakableBox),
		OBJECT(MODEL_BREAKABLE_BOX, 36, 28600, -499, 0, 0, 0, 0x00000000, bhvBreakableBox),
		OBJECT(MODEL_BREAKABLE_BOX, 36, 28600, -699, 0, 0, 0, 0x00000000, bhvBreakableBox),
		OBJECT(MODEL_BREAKABLE_BOX, 236, 28600, -699, 0, 0, 0, 0x00000000, bhvBreakableBox),
		OBJECT(MODEL_BREAKABLE_BOX, 236, 26245, -499, 0, 0, 0, 0x00000000, bhvBreakableBox),
		OBJECT(MODEL_BREAKABLE_BOX, 36, 26245, -499, 0, 0, 0, 0x00000000, bhvBreakableBox),
		OBJECT(MODEL_BREAKABLE_BOX, 36, 26245, -699, 0, 0, 0, 0x00000000, bhvBreakableBox),
		OBJECT(MODEL_BREAKABLE_BOX, 236, 26245, -699, 0, 0, 0, 0x00000000, bhvBreakableBox),
		OBJECT(MODEL_BREAKABLE_BOX, 236, 23390, -499, 0, 0, 0, 0x00000000, bhvBreakableBox),
		OBJECT(MODEL_BREAKABLE_BOX, 36, 23390, -499, 0, 0, 0, 0x00000000, bhvBreakableBox),
		OBJECT(MODEL_BREAKABLE_BOX, 36, 23390, -699, 0, 0, 0, 0x00000000, bhvBreakableBox),
		OBJECT(MODEL_BREAKABLE_BOX, 236, 23390, -699, 0, 0, 0, 0x00000000, bhvBreakableBox),
		OBJECT(MODEL_BREAKABLE_BOX, 236, 20620, -499, 0, 0, 0, 0x00000000, bhvBreakableBox),
		OBJECT(MODEL_BREAKABLE_BOX, 36, 20620, -499, 0, 0, 0, 0x00000000, bhvBreakableBox),
		OBJECT(MODEL_BREAKABLE_BOX, 36, 20620, -699, 0, 0, 0, 0x00000000, bhvBreakableBox),
		OBJECT(MODEL_BREAKABLE_BOX, 236, 20620, -699, 0, 0, 0, 0x00000000, bhvBreakableBox),
		OBJECT(MODEL_BREAKABLE_BOX, 236, 19780, -499, 0, 0, 0, 0x00000000, bhvBreakableBox),
		OBJECT(MODEL_BREAKABLE_BOX, 36, 19780, -499, 0, 0, 0, 0x00000000, bhvBreakableBox),
		OBJECT(MODEL_BREAKABLE_BOX, 36, 19780, -699, 0, 0, 0, 0x00000000, bhvBreakableBox),
		OBJECT(MODEL_BREAKABLE_BOX, 236, 19780, -699, 0, 0, 0, 0x00000000, bhvBreakableBox),
		OBJECT(MODEL_BREAKABLE_BOX, 236, 19222, -499, 0, 0, 0, 0x00000000, bhvBreakableBox),
		OBJECT(MODEL_BREAKABLE_BOX, 36, 19222, -499, 0, 0, 0, 0x00000000, bhvBreakableBox),
		OBJECT(MODEL_BREAKABLE_BOX, 36, 19222, -699, 0, 0, 0, 0x00000000, bhvBreakableBox),
		OBJECT(MODEL_BREAKABLE_BOX, 236, 19222, -699, 0, 0, 0, 0x00000000, bhvBreakableBox),
		OBJECT(MODEL_BREAKABLE_BOX, 236, 19022, -499, 0, 0, 0, 0x00000000, bhvBreakableBox),
		OBJECT(MODEL_BREAKABLE_BOX, 36, 19022, -499, 0, 0, 0, 0x00000000, bhvBreakableBox),
		OBJECT(MODEL_BREAKABLE_BOX, 36, 19022, -699, 0, 0, 0, 0x00000000, bhvBreakableBox),
		OBJECT(MODEL_BREAKABLE_BOX, 236, 19022, -699, 0, 0, 0, 0x00000000, bhvBreakableBox),
		OBJECT(MODEL_BREAKABLE_BOX, 236, 18822, -499, 0, 0, 0, 0x00000000, bhvBreakableBox),
		OBJECT(MODEL_BREAKABLE_BOX, 36, 18822, -499, 0, 0, 0, 0x00000000, bhvBreakableBox),
		OBJECT(MODEL_BREAKABLE_BOX, 36, 18822, -699, 0, 0, 0, 0x00000000, bhvBreakableBox),
		OBJECT(MODEL_BREAKABLE_BOX, 236, 18822, -699, 0, 0, 0, 0x00000000, bhvBreakableBox),
		OBJECT(MODEL_BREAKABLE_BOX, 236, 18622, -499, 0, 0, 0, 0x00000000, bhvBreakableBox),
		OBJECT(MODEL_BREAKABLE_BOX, 36, 18622, -499, 0, 0, 0, 0x00000000, bhvBreakableBox),
		OBJECT(MODEL_BREAKABLE_BOX, 36, 18622, -699, 0, 0, 0, 0x00000000, bhvBreakableBox),
		OBJECT(MODEL_BREAKABLE_BOX, 236, 18622, -699, 0, 0, 0, 0x00000000, bhvBreakableBox),
		MARIO_POS(0x01, 0, 541, 29861, -62),
		OBJECT(MODEL_NONE, 541, 29861, -62, 0, 0, 0, 0x000A0000, bhvSpinAirborneWarp),
		TERRAIN(castle_grounds_area_1_collision),
		MACRO_OBJECTS(castle_grounds_area_1_macro_objs),
		SET_BACKGROUND_MUSIC(0x00, SEQ_LEVEL_GRASS),
		TERRAIN_TYPE(TERRAIN_GRASS),
		/* Fast64 begin persistent block [area commands] */
		/* Fast64 end persistent block [area commands] */
	END_AREA(),

	FREE_LEVEL_POOL(),
	MARIO_POS(0x01, 0, 541, 29861, -62),
	CALL(0, lvl_init_or_update),
	CALL_LOOP(1, lvl_init_or_update),
	CLEAR_LEVEL(),
	SLEEP_BEFORE_EXIT(1),
	EXIT(),
};
