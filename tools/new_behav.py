#!/bin/python3

B_H = "include/behavior_data.h"
B_C = "data/behavior_data.c"
b_folder = "src/game/behaviors/"
f_proto_file = "src/game/obj_behaviors.h"

def write_funcs(nm):
	with open(b_folder + "%s.c" % nm, "w+") as f:
		f.write("""#include <ultra64.h>
#include "game/object_helpers.h"
#include "engine/math_util.h"

void bhv_%s_init(void) {
	
}
void bhv_%s_loop(void) {
	
}
""" % (nm, nm))
	with open(f_proto_file, "a") as f:
		f.write("\n")
		f.write("void bhv_%s_init(void); void bhv_%s_loop(void);" % (nm,nm))

def write_behavior(nm):
	with open(B_C, "a") as f:
		f.write("\n")
		f.write("""
extern void bhv_%s_init();
extern void bhv_%s_loop();
const BehaviorScript bhv%s[] = {
	BEGIN(OBJ_LIST_DEFAULT),
	CALL_NATIVE(bhv_%s_init),
	BEGIN_LOOP(),
		CALL_NATIVE(bhv_%s_loop),
	END_LOOP(),
};
""" % (nm, nm, nm, nm, nm))
	with open(B_H, "a") as f:
		f.write("\n")
		f.write("extern const BehaviorScript bhv%s[];" % nm)

import sys
bname = sys.argv[1]

write_behavior(bname)
write_funcs(bname)
