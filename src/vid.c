#include "vid.h"
#include "sdl.h"


/* TODO Get those from the user */
static const u32 WINDOW_WIDTH = 640;
static const u32 WINDOW_HEIGHT = 480;

/* Color palette used for converting 8bit colors to 32bit */
static u32 PALLETE[256];
static u32* BACKBUFFER = NULL;

Vid VID;

static QResult load_pallete()
{
        MString pallete_name = mstr_from_cstr("gfx/palette.lmp");
        u8* data = com_file_find(pallete_name, NULL);
        mstr_destroy(pallete_name);
        check(data, "Failed to load pallete");
        
        u8* walker = data;
        for (size_t i = 0; i < 256; ++i) {
                u8 red = *walker++;
                u8 green = *walker++;
                u8 blue = *walker++;

                PALLETE[i] = ((red << 16) | (green << 8) | blue);
        }
        return Q_OK;
error:
        return Q_ERR;
}

QResult vid_init()
{
        check(sdl_start("quake", WINDOW_WIDTH, WINDOW_HEIGHT), "Failed to initialize SDL");
        BACKBUFFER = SDL_BACKBUFFER;
        check(load_pallete(), "Failed to load pallete");
        VID.backbuffer = BACKBUFFER;
        VID.buf_height = WINDOW_HEIGHT;
        VID.buf_width = WINDOW_WIDTH;
        VID.palette = PALLETE;
        return Q_OK;
error:
        return Q_ERR;
}

void vid_close()
{
        sdl_end();
}

void vid_update()
{
        sdl_swap_buffers();
}
