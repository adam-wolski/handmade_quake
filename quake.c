#include "quakedef.h"
#include "./tests/tests.h"

void run_tests();

int main(int argc, char* argv[])
{
        com_init_argv(argc, argv);
        if (com_check_parm(mstr_from_cstr("run_tests"))) {
                run_tests();
                return 0;
        }
        vid_init();
        capture_events_test();
        vid_close();
        return 0;
}

void run_tests() {
        test_mstring();
}
