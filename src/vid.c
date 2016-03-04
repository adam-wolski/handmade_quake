#include "vid.h"
#include "sdl.h"


/* TODO Get those from the user */
static const u32 WINDOW_WIDTH = 640;
static const u32 WINDOW_HEIGHT = 480;


void vid_init()
{
        sdl_start("quake", WINDOW_WIDTH, WINDOW_HEIGHT);
}

void vid_close()
{
        sdl_end();
}
