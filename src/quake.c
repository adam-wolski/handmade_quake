#include "quakedef.h"

int main(int argc, char* argv[])
{
        com_init_argv(argc, argv);
        vid_init();
        capture_events_test();
        vid_close();
        return 0;
}
