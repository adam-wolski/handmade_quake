#include "../src/sys.h"
#include "./minunit/minunit.h"
#include <unistd.h>

static const char* test_read_path = "./tests/test_content/test_data.txt";
static const char* test_write_path = "./tests/test_content/test_data_w.txt";

MU_TEST(test_file_read_write) {
        MString rpath = mstr_from_cstr(test_read_path);
        FileHandleID rid;
        size_t size;
        char* cwd = calloc(100, sizeof(char));
        getcwd(cwd, 100);
        log_info("Current working directory: %s", cwd);
        mu_assert(sys_file_open_read(rpath, &rid, &size), "Failed to open a file.");
        char* rdata = calloc(2, sizeof(char));
        mu_assert(sys_file_read(rid, rdata, 1), "Failed to read a file.");
        rdata[1] = '\0';
        mu_assert(strcmp((const char*)rdata, "R") == 0, "Wrong data after file read.");
        mu_assert(sys_file_seek(rid, 0), "Failed to seek on file.");
        MString wpath = mstr_from_cstr(test_write_path);
        FileHandleID wid;
        mu_assert(sys_file_open_write(wpath, &wid), "Failed to open file for writing.");
        void* data = calloc(size, sizeof(u8));
        mu_assert(sys_file_read(rid, data, size), "Failed to read a file.");
        mu_assert(sys_file_write(wid, data, size), "Failed to write to a file.");

        mstr_destroy(rpath);
        mstr_destroy(wpath);
        sys_file_close(rid);
        sys_file_close(wid);
        free(rdata);
        free(data);
        free(cwd);
}

MU_TEST_SUITE(test_suite) {
        MU_RUN_TEST(test_file_read_write);
}

int sys_tests()
{
        MU_RUN_SUITE(test_suite);
        MU_REPORT();
        return 0;
}
