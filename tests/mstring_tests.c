#include "./minunit/minunit.h"
#include "../src/mstring.h"

MU_TEST(test_create) {
        MString test = mstr_from_cstr("TEST");
        mu_assert(test->slen == 4, "String length should be 4");
        mu_assert(test->mlen == 5, "MString should have allocated 5 bytes of memory");
        mu_check(test->data[0] == 'T');
        mu_check(test->data[1] == 'E');
        mu_check(test->data[2] == 'S');
        mu_check(test->data[3] == 'T');
        mstr_destroy(test);
}

MU_TEST_SUITE(test_suite) {
        MU_RUN_TEST(test_create);
}

int mstring_tests()
{
        MU_RUN_SUITE(test_suite);
        MU_REPORT();
        return 0;
}
