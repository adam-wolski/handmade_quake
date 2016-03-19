#include "../src/pack.h"
#include "./minunit/minunit.h"

const char* pak_path = "./content/Id1/PAK0.PAK";

MU_TEST(test_pack_load) {
        MString path = mstr_from_cstr(pak_path);
        Pack* pack = pack_load(path);
        mu_assert(pack, "Failed to create pack");
        mu_assert(pack->num_files == 339, "Found wrong number of files.");
        mu_assert(strcmp(pack->packname, (const char*)path->data) == 0,
                  "Wrong packname.");
        mu_assert(strcmp(pack->pack_files[0].filename, "sound/items/r_item1.wav") == 0,
                  "Wrong first file.");
        mu_assert(strcmp(pack->pack_files[338].filename, "maps/e1m8.bsp") == 0,
                  "Wrong last file.");

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
