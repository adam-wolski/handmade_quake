#include "../src/common.h"
#include "./minunit/minunit.h"

MU_TEST(test_args) {
        char* argv[3];
        argv[0] = "Test string 1";
        argv[1] = "avocado";
        argv[2] = "bananas";
        com_init_argv(3, argv);

        MString t = mstr_from_cstr("bananas");
        mu_assert(com_check_parm(t), "Wrong return value on test");

        MString t2 = mstr_from_cstr("Not Existing String");
        mu_assert(com_check_parm(t2) == false, "Wrong return value on test");

        mstr_destroy(t);
        mstr_destroy(t2);
        com_clear_argv();
}

MU_TEST(test_atoi) {
        MString t1 = mstr_from_cstr("1"); 
        mu_assert(com_atoi(t1) == 1, "Wrong number");
        mstr_destroy(t1);

        MString t2 = mstr_from_cstr("5789123"); 
        mu_assert(com_atoi(t2) == 5789123, "Wrong number");
        mstr_destroy(t2);

        MString t3 = mstr_from_cstr("0xFF"); 
        mu_assert(com_atoi(t3) == 255, "Wrong number");
        mstr_destroy(t3);

        MString t4 = mstr_from_cstr("0X009"); 
        mu_assert(com_atoi(t4) == 9, "Wrong number");
        mstr_destroy(t4);

        MString t5 = mstr_from_cstr("0X000"); 
        mu_assert(com_atoi(t5) == 0, "Wrong number");
        mstr_destroy(t5);
}

MU_TEST_SUITE(test_suite) {
        MU_RUN_TEST(test_args);
        MU_RUN_TEST(test_atoi);
}

int common_tests()
{
        MU_RUN_SUITE(test_suite);
        MU_REPORT();
        return 0;
}
