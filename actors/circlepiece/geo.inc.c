#include "src/game/envfx_snow.h"


extern Gfx cLava[];
extern Gfx cFinish[];
extern Gfx cBreak[];
const GeoLayout circlepiece_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_SWITCH_CASE(4, geo_switch_anim_state),
			GEO_OPEN_NODE(),
				GEO_DISPLAY_LIST(LAYER_OPAQUE, circlepiece_Circle_mesh_layer_1),
				GEO_DISPLAY_LIST(LAYER_OPAQUE, cLava),
				GEO_DISPLAY_LIST(LAYER_OPAQUE, cFinish),
				GEO_DISPLAY_LIST(LAYER_OPAQUE, cBreak),
			GEO_CLOSE_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, circlepiece_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
