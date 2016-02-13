#pragma once
#include "quakedef.h"

void vid_init();
void vid_close();
void capture_events_test();

extern Display *dis;
extern int screen;
extern Window win;
extern GC gc;
