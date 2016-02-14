#include "quakedef.h"

int main(int argc, char* argv[])
{
        /* Initialize game arguments and host */
        com_init_argv(argc, argv);
        host_init();

        /* Main game loop */
        f64 oldtime = sys_get_time();
        while(IS_RUNNING) {
                /* Check os events */
                sys_capture_events();
                
                f64 newtime = sys_get_time();
                f64 time = newtime - oldtime;

                host_frame(time);
        }

        /* End what you started */
        host_close();
        com_clear_argv();

        return 0;
}
