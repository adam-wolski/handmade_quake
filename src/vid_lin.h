#pragma once
#include "quakedef.h"

void vid_init();
void vid_close();
void vid_redraw();

extern Display *dis;
extern int screen;
extern Window win;
extern GC gc;
