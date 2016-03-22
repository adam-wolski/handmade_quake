#include "../src/common.h"
#include "./minunit/minunit.h"

MU_TEST(test_args) {
        char* argv[3];
        argv[0] = "Test string 1";
        argv[1] = "avocado";
        argv[2] = "bananas";
        com_arg_init(3, argv);

        MString t = mstr_from_cstr("bananas");
        mu_assert(com_arg_check(t), "Wrong return value on test");

        MString t2 = mstr_from_cstr("Not Existing String");
        mu_assert(com_arg_check(t2) == false, "Wrong return value on test");

        mstr_destroy(t);
        mstr_destroy(t2);
        com_arg_clear();
}

MU_TEST(test_files) {
        mu_assert(com_file_init(), "Failed to initialize file system");
        u8* file = NULL;
        size_t file_size;
        MString file_name = mstr_from_cstr("sound/items/r_item1.wav");
        file = com_file_find(file_name, &file_size);
        mu_assert(file, "Failed to find a file.");

        mstr_destroy(file_name);
        free(file);

        file_name = mstr_from_cstr("maps/e1m8.bsp");
        file = com_file_find(file_name, &file_size);
        mu_assert(file, "Failed to find a file.");

        com_file_clear();
        free(file);
        mstr_destroy(file_name);
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

MU_TEST(test_x8_to_32) {
        u8 bytes[4];
        bytes[0] = 5; /*  0000 0101 */
        bytes[1] = 10; /* 0000 1010 */
        bytes[2] = 4; /*  0000 0100 */
        bytes[3] = 1; /*  0000 0001 */
        /*0000 0000 0000 0101 0000 1010 0000 0100*/
        u32 r = com_3x8_to_32(bytes);
        mu_assert(r == 330244,
                  "Wrong return value from 3x8_to_32");
        r = com_4x8_to_32(bytes);
        /*0000 0101 0000 1010 0000 0100 0000 0001*/
        mu_assert(r == 84542465,
                  "Wrong return value from 4x8_to_32");
}

MU_TEST_SUITE(test_suite) {
        MU_RUN_TEST(test_args);
        MU_RUN_TEST(test_files);
        MU_RUN_TEST(test_atoi);
        MU_RUN_TEST(test_x8_to_32);
}

int common_tests()
{
        MU_RUN_SUITE(test_suite);
        MU_REPORT();
        return 0;
}
