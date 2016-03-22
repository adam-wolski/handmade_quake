#pragma once
#include "quakedef.h"

typedef struct {
        u32* backbuffer;
        u32* palette;
        size_t buf_width;
        size_t buf_height;
}Vid;

extern Vid VID;

QResult vid_init();
void vid_close();
void vid_update();
