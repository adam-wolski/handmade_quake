#include "../src/pack.h"
#include "./minunit/minunit.h"

const char* pak_path = "./content/Id1/PAK0.PAK";

MU_TEST(test_pack_load) {
        MString path = mstr_from_cstr(pak_path);
        Pack* pack = pack_load(path);
        mu_assert(pack, "Failed to create pack");

        free(pack);
        mstr_destroy(path);
}

MU_TEST_SUITE(test_suite) {
        MU_RUN_TEST(test_pack_load);
}

int pack_tests()
{
        MU_RUN_SUITE(test_suite);
        MU_REPORT();
        return 0;
}
