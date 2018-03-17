/*
	harris - a strategy game
	Copyright (C) 2012-2015 Edward Cree

	licensed under GPLv3+ - see top of harris.c for details
	
	load_data: load game entity data
*/

#include <stdbool.h>

int load_data(void); // performs all the loads below

int load_bombers(void); // -> types
int load_tech_data(void); // performs load_techs, load_btechs, load_etechs
int load_techs(void); // -> techs
int load_btechs(void); // -> btechs
int load_etechs(void); // -> etechs
int load_fighters(void); // -> ftypes
int load_ftrbases(void); // -> fbases
int load_locations(void); // -> locs
int load_targets(void); // -> targs, locs
int load_flaksites(void); // -> flaks
int load_events(void); // -> event
int load_texts(void); // -> evtext, types.text, types.newtext, ftypes.text, ftypes.newtext
int load_intel(void); // -> targs.p_intel
int load_images(void); // many outputs
int load_starts(void); // -> starts
