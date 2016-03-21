#include "./minunit/minunit.h"
#include "../src/mstring.h"
#include <string.h>

MU_TEST(test_create) {
        MString test = mstr_from_cstr("TEST");
        mu_assert(test->slen == 4, "String length should be 4");
        mu_assert(test->mlen == 5, "MString should have allocated 5 bytes of memory");
        mu_check(test->data[0] == 'T');
        mu_check(test->data[1] == 'E');
        mu_check(test->data[2] == 'S');
        mu_check(test->data[3] == 'T');
        mstr_destroy(test);

        MString test_format = mstr_from_format("%d %s TEST", 50, "dog");
        mu_assert(strcmp((const char*)test_format->data, "50 dog TEST")== 0,
                  "Wrong formated string output");
        mstr_destroy(test_format);
}

MU_TEST(test_compare) {
        MString a = mstr_from_cstr("test string");
        MString b = mstr_from_cstr("test string");
        mu_check(mstr_cmp(a, b) == 0);
        mu_check(mstr_compare(a, b));
        mstr_destroy(a);
        a = mstr_from_cstr("test string2");
        mu_check(mstr_cmp(a, b) == 1);
        mu_check(mstr_compare(a, b) == false);
        mstr_destroy(a);
        mstr_destroy(b);
}

MU_TEST_SUITE(test_suite) {
        MU_RUN_TEST(test_create);
        MU_RUN_TEST(test_compare);
}

int mstring_tests()
{
        MU_RUN_SUITE(test_suite);
        MU_REPORT();
        return 0;
}
