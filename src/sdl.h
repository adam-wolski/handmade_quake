#pragma once
#include <SDL2/SDL.h>
#include "quakedef.h"

extern SDL_Window* SDL_WINDOW;
extern SDL_Renderer* SDL_RENDERER;
extern SDL_Texture* SDL_TEXTURE;
extern u32 SDL_WIDTH;
extern u32 SDL_HEIGHT;
extern u32* SDL_BACKBUFFER;

bool sdl_start(const char* title, u32 window_width, u32 window_height);
void sdl_color_to_backbuffer(SDL_Color* clr); 
void sdl_set_backbuffer(u32* buffer_data);
void sdl_swap_buffers();
void sdl_end();
bool sdl_capture_events();
u32  sdl_get_ticks();
