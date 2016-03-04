#include "sys.h"
#include "sdl.h"

/** Return elapsed time in seconds since program started **/
f64 sys_get_time()
{
        /* Sdl returns time in milliseconds */
        return (f64)sdl_get_ticks() / 1000.0;
}

void sys_capture_events()
{
        if (!sdl_capture_events()) {
                IS_RUNNING = false;
        }
}
