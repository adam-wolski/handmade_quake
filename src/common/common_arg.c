#include "../common.h"

#define CMD_LINE_LENGTH 256
MString COM_CMDLINE;
MString* COM_ARGV;
size_t  COM_ARGC;


/** Initialize game arguments. **/
QResult com_arg_init(const u32 argc, char** argv) 
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

       return Q_OK;

error:
       return Q_ERR;
}

/** Clear all the stored arguments, and free memory. **/
void com_arg_clear() 
{
        mstr_destroy(COM_CMDLINE);
        for (size_t i = 0; i < COM_ARGC; ++i) {
                mstr_destroy(COM_ARGV[i]);
        }
        free(COM_ARGV);
}

/** Return True if parameter 'parm' was found in game arguments. **/
bool com_arg_check(const MString parm) 
{
        for (size_t i = 1; i < COM_ARGC; ++i) {
                if (!mstr_cmp(COM_ARGV[i], parm)) {
                        return true;
                }
        }
        return false;
}
