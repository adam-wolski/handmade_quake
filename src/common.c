#include "quakedef.h"

#define CMD_LINE_LENGTH 256
MString COM_CMDLINE;
MString* COM_ARGV;
size_t  COM_ARGC;


/** Initialize game arguments. Returns False on memory error. **/
bool com_init_argv(const u32 argc, char** argv) 
{
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
       COM_CMDLINE = mstr_from_cstr(cmdline);

       COM_ARGV = calloc(MAX_NUM_ARGVS, sizeof(MString));
       check_mem(COM_ARGV);

       COM_ARGC = (size_t)argc;
       for (size_t k = 0; k < COM_ARGC; ++k) {
                COM_ARGV[k] = mstr_from_cstr(argv[k]);
       }

       return true;

error:
       return false;
}

/** Clear all the stored arguments, and free memory. **/
bool com_clear_argv() 
{
        mstr_destroy(COM_CMDLINE);
        for (size_t i = 0; i < COM_ARGC; ++i) {
                mstr_destroy(COM_ARGV[i]);
        }
        free(COM_ARGV);
        return true;
}

/** Return True if parameter 'parm' was found in game arguments. **/
bool com_check_parm(const MString parm) 
{
        for (size_t i = 1; i < COM_ARGC; ++i) {
                if (!mstr_cmp(COM_ARGV[i], parm)) {
                        return true;
                }
        }
        return false;
}

/** Convert string to integer value. **/
i32 com_atoi(const MString str) 
{
        unsigned char* data = mstr_to_chars(str);
        size_t len = str->slen;
        size_t i = 0;
        i32 result = 0;
        i32 mul = 1;
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
