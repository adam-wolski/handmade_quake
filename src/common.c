#include "quakedef.h"

#define CMD_LINE_LENGTH 256
Mstring com_cmdline;
Mstring* com_argv;
size_t  com_argc;

/*
===============================================================================================
        Function: com_init_argv
        Initialize game arguments.
        Returns False on memory error.
===============================================================================================
*/
bool com_init_argv(const uint32 argc, char** argv) {
       size_t n = 0;
       size_t i = 0;
       char cmdline[CMD_LINE_LENGTH];
       for (size_t j = 0; j < MAX_NUM_ARGVS && j < argc; ++j) {
               while ((j < CMD_LINE_LENGTH - 1) && argv[j][i]) {
                       cmdline[n++] = argv[j][i++];
               }
               if (n < CMD_LINE_LENGTH - 1) {
                       cmdline[n++] = ' ';
               }
               else {
                       break;
               }
       }

       cmdline[n] = 0;
       com_cmdline = mstr_from_cstr(cmdline);

       com_argv = calloc(MAX_NUM_ARGVS, sizeof(Mstring));
       check_mem(com_argv);

       com_argc = (size_t)argc;
       for (size_t k = 0; k < com_argc; ++k) {
                com_argv[k] = mstr_from_cstr(argv[k]);
       }

       return true;

error:
       return false;
}

/*
===============================================================================================
        Function: com_clear_argv
        Clear all the stored arguments, and free memory.
===============================================================================================
*/
bool com_clear_argv() {
        mstr_destroy(com_cmdline);
        for (size_t i = 0; i < com_argc; ++i) {
                mstr_destroy(com_argv[i]);
        }
        return true;
}


/*
===============================================================================================
        Function: com_check_parm
        Return True if parameter 'parm' was found in game arguments.
===============================================================================================
*/
bool com_check_parm(const Mstring parm) {
        for (size_t i = 1; i < com_argc; ++i) {
                if (!mstr_cmp(com_argv[i], parm)) {
                        return true;
                }
        }
        return false;
}

/*
===============================================================================================
        Function: com_atoi
        Convert string to integer value.
===============================================================================================
*/
int32 com_atoi(const Mstring str) {
        unsigned char* data = mstr_to_chars(str);
        size_t len = str->slen;
        size_t i = 0;
        int32 result = 0;
        int32 mul = 1;
        if (data[i] == '-') {
                mul = -1;
                ++i;
        }
        // Hex
        if (data[i] == '0' && (data[i+1] == 'x' || data[i+1] == 'X')) {
                i += 2;
                while (i < len) {
                        if (data[i] >= '0' && data[i] <= '9') {
                                result = result * 16 + data[i++] - '0'; 
                        } else if (data[i] >= 'a' && data[i] <= 'f') {
                                result = result * 16 + data[i++] - 'a' + 10;
                        } else if (data[i] >= 'A' && data[i] <= 'F') {
                                result = result * 16 + data[i++] - 'A' + 10;
                        } else {
                                break;
                        }
                }
                return result * mul;
        }

        // Decimal
        while (i < len) {
                if (data[i] < '0' || data[i] > '9') {
                        break;
                }
                result = result * 10 + data[i++] - '0'; 
        }

        return result * mul;
}
