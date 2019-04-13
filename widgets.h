/*
	harris - a strategy game
	Copyright (C) 2012-2015 Edward Cree

	licensed under GPLv3+ - see top of harris.c for details
	
	widgets: defines custom libatg widgets
*/
#include <atg.h>
#include "types.h"

atg_element *create_priority_selector(unsigned int *prio); // create a priority selector widget.  prio is put in userdata
atg_element *create_filter_switch(SDL_Surface *icon, int *value); // create a filter switch widget.  value is put in userdata
atg_element *create_bfilter_switch(unsigned int count, atg_colour bgcolour, SDL_Surface **icon, bool *value); // create a bitwise filter switch widget
atg_element *create_load_selector(bombertype *type, unsigned int *load); // create a bombload selector widget.  load is put in userdata
atg_element *create_time_spinner(Uint8 flags, int minval, int maxval, int step, int initvalue, const char *fmt, atg_colour fgcolour, atg_colour bgcolour); // create a time spinner widget
