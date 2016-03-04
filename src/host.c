#include "host.h"

/* Global IS_RUNNING var checked to be checked wherever you want. */
bool IS_RUNNING = false;
f64 TARGET_FPS = 72; /* Quake aims for 72, good to keep it the same for server compatibility */

/*
 * Host time variables are bound by fps and other bounds in host_filter_time 
 * While the REALTIME ones are used for unfiltered time keeping.
 */
f64 HOST_FRAMETIME = 0;
f64 HOST_TIME = 0;
f64 REALTIME = 0; /* Time without any filtering or bounds */
f64 OLD_REALTIME = 0; /* Last frame check */


void host_init() 
{
        IS_RUNNING = true;
        vid_init();
}

/** Check if time isn't too short to run a frame. **/
bool host_filter_time(f64 time)
{
        REALTIME += time; 
        if (REALTIME - OLD_REALTIME < 1.0/TARGET_FPS) {
                return false; /* Too fast */
        }
        
        HOST_FRAMETIME = REALTIME - OLD_REALTIME;
        OLD_REALTIME = REALTIME;

        /* TODO Store framerate specified by user and check it here for ability to lower fps */

        /* Don't allow to low or to high values */
        if (HOST_FRAMETIME > 0.1) {
                HOST_FRAMETIME = 0.1;
        }
        if (HOST_FRAMETIME < 0.001) {
                HOST_FRAMETIME = 0.001;
        }

        return true;
}

/** Update game by one frame. **/
void host_frame(f64 time) 
{
        host_filter_time(time);
}

/** Close subsystems and clear memory. **/
void host_close() 
{
        IS_RUNNING = false;
        vid_close();
}
