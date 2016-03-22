#include "sdl.h"
/* Here be globals, beware! */
SDL_Window* SDL_WINDOW;
SDL_Renderer* SDL_RENDERER;
SDL_Texture* SDL_TEXTURE;
u32* SDL_BACKBUFFER;
u32 SDL_WIDTH;
u32 SDL_HEIGHT;
static size_t SDL_BACKBUFFER_SIZE;

bool sdl_start(const char* title, u32 window_width, u32 window_height) 
{
        SDL_Init(SDL_INIT_VIDEO);
        SDL_WIDTH = window_width;
        SDL_HEIGHT = window_height;
        SDL_WINDOW = SDL_CreateWindow(title,
                                      SDL_WINDOWPOS_UNDEFINED,
                                      SDL_WINDOWPOS_UNDEFINED,
                                      SDL_WIDTH,
                                      SDL_HEIGHT,
                                      0);
        SDL_RENDERER = SDL_CreateRenderer(SDL_WINDOW, -1, 0);
        SDL_TEXTURE = SDL_CreateTexture(SDL_RENDERER,
                                        SDL_PIXELFORMAT_ARGB8888,
                                        SDL_TEXTUREACCESS_STATIC,
                                        SDL_WIDTH,
                                        SDL_HEIGHT);
        SDL_BACKBUFFER_SIZE = (size_t)(SDL_WIDTH * SDL_HEIGHT);
        SDL_BACKBUFFER = calloc(SDL_BACKBUFFER_SIZE, sizeof(u32));
        if (!SDL_BACKBUFFER) {
                return false;
        }
        return true;
}

/** Convert array of Color structs to u32 array. **/
void sdl_color_to_backbuffer(SDL_Color* clr) 
{
        for (size_t i = 0; i < SDL_BACKBUFFER_SIZE; i += (size_t)SDL_WIDTH) {
                for (size_t j = 0; j < (size_t)SDL_WIDTH; ++j) {
                        /* 
                         * Pixel format must be the same as in the CreateTexture function where we
                         * created texture for backbuffer.
                         * Which right now should be set to PIXEL_FORMAT_ARGB8888 
                         */
                        u32 iclr = (((u32)clr[i + j].a) << 24) |
                                   (((u32)clr[i + j].r) << 16) |
                                   (((u32)clr[i + j].g) << 8)  |
                                   ( (u32)clr[i + j].b);
                        SDL_BACKBUFFER[i + j] = iclr;
                }
        }
}

/**
 * Fill backbuffer with specified buffer_data.
 * buffer_data needs to be same size as SDL_BACKBUFFER otherwise can cause unexpected behaviour
 */
void sdl_set_backbuffer(u32* buffer_data) 
{
        for (size_t i = 0; i < SDL_BACKBUFFER_SIZE; i += (size_t)SDL_WIDTH) {
               for (size_t j = 0; j < (size_t)SDL_WIDTH; ++j) {
                       SDL_BACKBUFFER[i + j] = buffer_data[i + j];
               } 
        }
}

void sdl_swap_buffers() 
{
        SDL_UpdateTexture(SDL_TEXTURE, NULL, SDL_BACKBUFFER, SDL_WIDTH * sizeof(u32));
        SDL_RenderClear(SDL_RENDERER);
        SDL_RenderCopy(SDL_RENDERER, SDL_TEXTURE, NULL, NULL);
        SDL_RenderPresent(SDL_RENDERER);
}

void sdl_end() 
{
        free(SDL_BACKBUFFER);
        SDL_DestroyTexture(SDL_TEXTURE);
        SDL_DestroyRenderer(SDL_RENDERER);
        SDL_DestroyWindow(SDL_WINDOW);
        SDL_Quit();
}

/**
 * TODO Capture keystrokes to SDL_KEY_UP, SDL_KEY_DOWN and SDL_KEY_HELD.
 * Returns false on SDL_QUIT.
 **/
bool sdl_capture_events() 
{
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
                switch (event.type) {
                        case SDL_QUIT:
                                return false;
                                break;
                        default:
                                break;
                }
        }
        return true;
}

u32 sdl_get_ticks()
{
        return SDL_GetTicks();
}
